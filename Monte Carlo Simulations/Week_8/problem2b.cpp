#include<iostream>
#include<cmath>
#include <tuple>
#define onethird 1.0/3.0
using namespace std;
/* The control variate is u, therefore x + c(u-0.5)*/
tuple<double,double,double,double> Control_u2(int n){
    double u,us[100];  //u(0,1), 
    double x, y,u2;       //x = sqrt(1-u^2),y, u*u
    double est, estA;  //est.(integral), Control est.
    double mean, svs;  //mean, sample variance of estimator
    double meanA,svsA; //mean, var of control
    double co_xy,yvar,ybar;//covariance, y mean, variance of y
    double xbar,copt;

    u = ((double)rand()/(RAND_MAX));
    us[0] = u;
    y = u*u;
    x = sqrt(1-y);
    ybar = y;
    xbar = x;
    yvar = 0;
    co_xy = 0;
    for(int i = 1; i < 100; i++)
    {
         u = ((double)rand()/(RAND_MAX));
         us[i] = u;
         y = u*u;
         x = sqrt(1-y);
         yvar = yvar*(i - 1)/i  + (ybar - y)*(ybar - y)/(i + 1);
         ybar = ybar + (y - ybar)/(i + 1);
         xbar = xbar + (x - xbar)/(i + 1);
         co_xy = co_xy*(i - 1)/i + (x-xbar)*(y-ybar)/i; //recursive covariance
    }
    copt = -co_xy/yvar; // c_opt
    
    u2 = us[0]*us[0];
    est = sqrt(1-u2);
    estA = est + copt*(u2-onethird); 
    mean = est;
    meanA = estA;
    svs = 0;
    svsA = 0;
    for(int i = 1; i < 100; i++)
    {
         u2 = us[i]*us[i];
         x = sqrt(1-u2);
         y = x + copt*(u2 - onethird); //recycle y as the unbiased estimator
         svs = svs *(i - 1)/i  + (mean - x)*(mean - x)/(i + 1);
         svsA = svsA *(i - 1)/i  + (meanA - y)*(meanA - y)/(i + 1);
         mean = mean + (x - mean)/(i+1);
         meanA = meanA + (y - meanA)/(i+1);
        
    }
    
    for(int i = 100;i < n;i++){
         u = ((double)rand()/(RAND_MAX));
         u2 = u*u;
         x = sqrt(1-u2);
         y = x + copt*( u2 - onethird);
         svs = svs *(i - 1)/i  + (mean - x)*(mean - x)/(i + 1);
         svsA = svsA *(i - 1)/i  + (meanA - y)*(meanA - y)/(i + 1);
         mean = mean + (x - mean)/(i+1);
         meanA = meanA + (y - meanA)/(i+1);
    }
    return make_tuple(mean, meanA, svs,svsA);
}
int main(){
    int N[5]={100,1000,10000,100000,1000000};
    for(int i=0;i<5;i++){
        srand(1);       //set up the same random seed for comparison
        auto Var = Control_u2(N[i]);
        cout<<"The control variate is u^2, and N = "<<N[i]<<endl;
        cout<<"Value of crude MC estimator is "<<get<0>(Var)<<endl;
        cout<<"Value of control MC estimator is "<<get<1>(Var)<<endl;
        cout<<"Variance of crude MC estimator is "<<get<2>(Var)<<endl;
        cout<<"Variance of control MC estimator is "<<get<3>(Var)<<endl;
        cout<<endl;
    }
}