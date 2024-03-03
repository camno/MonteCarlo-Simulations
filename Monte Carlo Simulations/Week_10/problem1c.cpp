#include<iostream>
#include<cmath>
#include <tuple>
using namespace std;
/* g(x)  = 3 * x^2 */

tuple<double,double> MCIntegrelImpSamp(){
    double u;           // u(0,1)
    double x, y, x_;    // realization of exp(u^2)
    double est, estA;   // est.
    int n = 1000;       // 1000 points
    est = 0.0;
    estA = 0.0;
    for(int i = 0;i < n;i++){
         u = ((double)rand()/(RAND_MAX));
         x_ = pow(u,1.0/3.0);//inversion
         x = exp(u*u);
         y = exp(x_*x_)/(x_*x_); // h(x_)*f(x_)/g(x_)
         est = est + (x - est)/(i+1); 
         estA = estA + (y - estA)/(i+1);  
    }
    estA = estA/3.0;
    return make_tuple(est,estA);
}

tuple<double,double,double,double> getVars(int n){
    double x, y, xA;   // realizations
    double mean, svs;  //mean, sample variance of estimator
    double meanA,svsA; //mean, var of antithetic

    auto results = MCIntegrelImpSamp();
    x = double(get<0>(results));
    y = double(get<1>(results));
    xA = y;
    mean = x;
    meanA = xA;
    svs = 0;
    svsA = 0; 
    for(int i = 1; i < n; i++)
    {
        auto results = MCIntegrelImpSamp();
        x = double(get<0>(results));
        y = double(get<1>(results));
        xA = y;
        svs = svs *(i - 1)/i  + (mean - x)*(mean - x)/(i+1);
        mean = mean + (x-mean)/(i+1);
        svsA = svsA *(i - 1)/i  + (meanA - xA)*(meanA - xA)/(i+1);
        meanA = meanA + (xA-meanA)/(i+1);
    }
    return make_tuple(mean, meanA, svs, svsA);
}

int main(){
    int N=1000;
    srand(1);       //set up the same random seed for comparison
    auto Var = getVars(N);
    cout<<"For N = "<<N<<endl;
    cout<<"Mean Value of crude MC integrel is "<<get<0>(Var)<<endl;
    cout<<"Mean Value of Importance Sampling MC Integrel is "<<get<1>(Var)<<endl;
    cout<<"Variance of crude MC Integrel is "<<get<2>(Var)<<endl;
    cout<<"Variance of Importance Sampling MC Integrel is "<<get<3>(Var)<<endl;
    cout<<endl;
}
