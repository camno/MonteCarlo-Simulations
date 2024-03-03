#include<iostream>
#include<cmath>
#include <tuple>
#define pis 8.0*atan(1)
using namespace std;
/* The control variate is u, therefore x + c(u-0.5)*/
tuple<double,double,double,double> MCIntegrelVar(int n){
    double u,us[100];          // u(0,1), 
    double x, y;       //realization of exp(u^2)
    double est, estA;   //est.(integral), Control est.
    double mean, svs;  //mean, sample variance of estimator
    double meanA,svsA; //mean, var of control
    double co_xy,yvar,ybar;//covariance, y mean, variance of y
    double xbar,copt;

    u = ((double)rand()/(RAND_MAX));
    us[0] = u;
    x = exp(u*u);
    y = u;
    ybar = y;
    xbar = x;
    yvar = 0;
    co_xy = 0;
    for(int i = 1; i < 100; i++)
    {
         u = ((double)rand()/(RAND_MAX));
         us[i] = u;
         x = exp(u*u);
         y = u;
         yvar = yvar*(i - 1)/i  + (ybar - y)*(ybar - y)/(i + 1);
         ybar = ybar + (y - ybar)/(i + 1);
         xbar = xbar + (x - xbar)/(i + 1);
         co_xy = co_xy*(i - 1)/i + (x-xbar)*(y-ybar)/i; //recursive covariance
    }
    copt = -co_xy/yvar; // c_opt
    
    est = exp(us[0]*us[0]);
    estA = est + copt*(us[0]-0.5); 
    mean = est;
    meanA = estA;
    svs = 0;
    svsA = 0;
    for(int i = 1; i < 100; i++)
    {
         x = exp(us[i]*us[i]);
         y = x + copt*(us[i]-0.5);
         est = est + (x - est)/(i+1);
         estA = estA + (y - estA)/(i+1);
         svs = svs *(i - 1)/i  + (mean - est)*(mean - est)/(i + 1);
         svsA = svsA *(i - 1)/i  + (meanA - estA)*(meanA - estA)/(i + 1);
         mean = mean + (est - mean)/(i+1);
         meanA = meanA + (estA - meanA)/(i+1);
        
    }
    
    for(int i = 100;i < n;i++){
         u = ((double)rand()/(RAND_MAX));
         x = exp(u*u);
         y = x + copt*(u-0.5);
         est = est + (x - est)/(i+1);
         estA = estA + (y-estA)/(i+1);
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
        cout<<"Mean Value of crude MC integrel is "<<get<0>(Var)<<endl;
        cout<<"Mean Value of control MC Integrel is "<<get<1>(Var)<<endl;
        cout<<"Variance of crude MC Integrel is "<<get<2>(Var)<<endl;
        cout<<"Variance of control MC Integrel is "<<get<3>(Var)<<endl;
        cout<<endl;
    }
}