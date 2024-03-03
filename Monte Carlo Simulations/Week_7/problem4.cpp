#include<iostream>
#include<cmath>
#include <tuple>
using namespace std;
tuple<double,double> numTrail(){
    double u,uA,newU,newUA;//u~(0,1)
    double tmp,uold,newUold;
    double i,j;
    u = 0;
    uA = 0;
    newU = ((double)rand()/(RAND_MAX));
    newUA = 1 - newU;
    i = 1;
    j = 1;

    while((u <= newU) || (uA <= newUA)){
        uold = u;    
        newUold = newU;
        if (u <= newU) {
            u = newU;
            newU = ((double)rand()/(RAND_MAX));
            i = i + 1 ;
        }

        if (uA <= newUA) {
             uA = newUA;
             if(uold <= newUold){
                 newUA = 1 - newU; 
             }else{
                 newUA = 1 - ((double)rand()/(RAND_MAX));
             }
             j = j + 1 ;
         }   
    }
    return make_tuple(i,j);
}
tuple<double,double,double,double> getVars(int n){ 
    double x, y, xA;   // realizations
    double mean, svs;  //mean, sample variance of estimator
    double meanA,svsA; //mean, var of antithetic

    auto results = numTrail();
    x = get<0>(results);
    y = get<1>(results);
    xA = (x+y)/2;
    mean = x;
    meanA = xA;
    svs = 0;
    svsA = 0;
    for(int i = 1; i < n; i++)
    {
        auto results = numTrail();
        x = double(get<0>(results));
        y = double(get<1>(results));
        xA = (x+y)/2;
        svs = svs *(i - 1)/i  + (mean - x)*(mean - x)/(i+1);
        mean = mean + (x-mean)/(i+1);

        svsA = svsA *(i - 1)/i  + (meanA - xA)*(meanA - xA)/(i+1);
        meanA = meanA + (xA-meanA)/(i+1);
    }
    return make_tuple(mean, meanA, svs, svsA);
}

int main(){
    int N[5]={100,1000,10000,100000,1000000};
    for(int i=0;i<5;i++){
        srand(1);       //set up the same random seed for comparison
        auto Var = getVars(N[i]);
        cout<<"For N = "<<N[i]<<endl;
        cout<<"Value of the L is "<<get<0>(Var)<<endl;
        cout<<"Value of antithetic L is "<<get<1>(Var)<<endl;
        cout<<"Variance of normal L is "<<get<2>(Var)<<endl;
        cout<<"Variance of antithetic L is "<<get<3>(Var)<<endl;
        cout<<endl;
    }
}