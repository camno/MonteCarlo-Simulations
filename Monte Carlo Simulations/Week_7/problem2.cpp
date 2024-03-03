#include<iostream>
#include<cmath>
#include <tuple>
#define pis 8.0*atan(1)
using namespace std;

tuple<double,double,double,double> MCIntegrelVar(int n){
    double u;          // u(0,1), 
    double x, y;          //realization of exp(u^2)
    double est,estA;        //est.(integral), antithetic est.
    double mean, svs;  //mean, sample variance of estimator
    double meanA,svsA; //mean, var of antithetic

    u = ((double)rand()/(RAND_MAX));
    x = exp(u*u);
    y = exp((1-u)*(1-u));
    est = x ;
    estA = (x+y)/2;
    svs = 0;
    svsA = 0;
    mean = est;
    meanA = estA;
    for(int i = 1; i < n; i++)
    {
         u = ((double)rand()/(RAND_MAX));
         x = exp(u*u);
         y = exp((1-u)*(1-u));
         est = est + (x - est)/(i+1);
         estA = estA + ((x+y)/2-estA)/(i+1);
         svs = svs *(i - 1)/i  + (mean - est)*(mean - est)/(i + 1);
         svsA = svsA *(i - 1)/i  + (meanA - estA)*(meanA - estA)/(i + 1);
         mean = mean + (est - mean)/(i+1);
         meanA = meanA + (estA - meanA)/(i+1);
    }
    return make_tuple(mean, meanA, svs,svsA);
}
int main(){
    int N[5]={100,1000,10000,100000,1000000};
    for(int i=0;i<5;i++){
        srand(1);       //set up the same random seed for comparison
        auto Var = MCIntegrelVar(N[i]);
        cout<<"For N = "<<N[i]<<endl;
        cout<<"Value of the MC integrel is "<<get<0>(Var)<<endl;
        cout<<"Value of antithetic MC Integrel is "<<get<1>(Var)<<endl;
        cout<<"Variance of normal MC Integrel is "<<get<2>(Var)<<endl;
        cout<<"Variance of antithetic MC Integrel is "<<get<3>(Var)<<endl;
        cout<<endl;
    }
}