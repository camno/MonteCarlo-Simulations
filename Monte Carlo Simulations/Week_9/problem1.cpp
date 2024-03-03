#include<iostream>
#include<cmath>
#include <tuple>
using namespace std;

tuple<double,double> twoDices(){
    double u1,u2; //u1,u2~u(0,1)
    double e1,e2; //exp(1),exp(0.5)
    double i,j;//j is the control variate
    u1 = ((double)rand()/(RAND_MAX));
    u2 = ((double)rand()/(RAND_MAX));
    e1 = -log(u1);
    e2 = -2*log(u2);
    i = 0;
    j = 0;
    if ((e1+e2>4)) {
        i = 1.0;
    }
    if (e2>=4.0) {
        j = 1.0;
    }else{
        j = exp(e2 - 4.0);
    }
    return make_tuple(i,j);
}
tuple<double,double,double,double> getVars(int n){
    double u, copt;          // u(0,1), 
    double x, y, xA;   // realizations
    double xbar,ybar,yvar;
    double mean, svs;  //mean, sample variance of estimator
    double meanA,svsA; //mean, var of antithetic

    auto results = twoDices();
    x = get<0>(results);
    y = get<1>(results);
    xA = y;
    mean = x;
    meanA = xA;
    svs = 0;
    svsA = 0;   
    for(int i = 1; i < n; i++)
    {
        auto results = twoDices();
        x = double(get<0>(results));
        y = double(get<1>(results));
        xA = y;
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
        srand(4);       //set up the same random seed for comparison
        auto Var = getVars(N[i]);
        cout<<"For N = "<<N[i]<<endl;
        cout<<"Value of the crude MC is "<<get<0>(Var)<<endl;
        cout<<"Value of Conditioning MC is "<<get<1>(Var)<<endl;
        cout<<"Variance of the crude MC is "<<get<2>(Var)<<endl;
        cout<<"Variance of Conditioning MC is "<<get<3>(Var)<<endl;
        cout<<endl;
    }
}