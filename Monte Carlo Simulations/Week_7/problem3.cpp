#include<iostream>
#include<cmath>
#include <tuple>
using namespace std;
tuple<double,double> numGreatOne(){
    double u,sum,sumA;//u~(0,1), sum of us, sum of antithetics
    double i,j;
    sum = 0;
    sumA = 0;
    i = 0;
    j = 0;
    while( (sum<= 1) || (sumA <= 1) ){
        u = ((double)rand()/(RAND_MAX));
        if(sum<= 1){
            sum = sum + u;
            i = i + 1;
        }
        if(sumA<=1){
            sumA = sumA + 1 - u;
            j = j + 1;
        }
    }
    return make_tuple(i,j);
}
tuple<double,double,double,double> getVars(int n){
    double u;          // u(0,1), 
    double x, y, xA;   // realizations
    double mean, svs;  //mean, sample variance of estimator
    double meanA,svsA; //mean, var of antithetic

    auto results = numGreatOne();
    x = get<0>(results);
    y = get<1>(results);
    xA = (x+y)/2;
    mean = x;
    meanA = xA;
    svs = 0;
    svsA = 0;
    for(int i = 1; i < n; i++)
    {
        auto results = numGreatOne();
        x = double(get<0>(results));
        y = double(get<1>(results));
        xA = (x+y)/2;
        svs = svs *(i - 1)/i  + (mean - x)*(mean - x)/(i+1);
        mean = mean + (x-mean)/(i+1);

        svsA = svsA *(i - 1)/i  + (meanA - xA)*(meanA - xA)/(i+1);
        meanA = meanA + (xA-meanA)/(i+1);
    }
    return make_tuple(mean, meanA, svs,svsA);
}

int main(){
    int N[5]={100,1000,10000,100000,1000000};
    for(int i=0;i<5;i++){
        srand(1);       //set up the same random seed for comparison
        auto Var = getVars(N[i]);
        cout<<"For N = "<<N[i]<<endl;
        cout<<"Value of the M is "<<get<0>(Var)<<endl;
        cout<<"Value of antithetic M is "<<get<1>(Var)<<endl;
        cout<<"Variance of normal M is "<<get<2>(Var)<<endl;
        cout<<"Variance of antithetic M is "<<get<3>(Var)<<endl;
        cout<<endl;
    }
}