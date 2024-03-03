#include<iostream>
#include<cmath>
#include <tuple>
using namespace std;
/* The control variate is u, therefore x + c(u-0.5)*/
tuple<double,double,double,double> Control_u(int n){
    double u,us[100];  //u(0,1), 
    double x, y;       //x = sqrt(1-u^2),y = u
    double est, estA;  //est.(integral), Control est.
    double mean, svs;  //mean, sample variance of estimator
    double meanA,svsA; //mean, var of control
    double co_xy,yvar,ybar;//covariance, y mean, variance of y
    double xbar,copt;

    u = ((double)rand()/(RAND_MAX));
    us[0] = u;
    x = sqrt(1-u*u);
    y = u;
    ybar = y;
    xbar = x;
    yvar = 0;
    co_xy = 0;
    for(int i = 1; i < 100; i++)
    {
         u = ((double)rand()/(RAND_MAX));
         us[i] = u;
         x = sqrt(1-u*u);
         y = u;
         yvar = yvar*(i - 1)/i  + (ybar - y)*(ybar - y)/(i + 1);
         ybar = ybar + (y - ybar)/(i + 1);
         xbar = xbar + (x - xbar)/(i + 1);
         co_xy = co_xy*(i - 1)/i + (x-xbar)*(y-ybar)/i; //recursive covariance
    }
    copt = -co_xy/yvar; // c_opt
    
    est = sqrt(1-us[0]*us[0]);
    estA = est + copt*(us[0]-0.5); 
    mean = est;
    meanA = estA;
    svs = 0;
    svsA = 0;
    for(int i = 1; i < 100; i++)
    {
         x = sqrt(1-us[i]*us[i]);
         y = x + copt*(us[i]-0.5); //recycle y as the unbiased estimator
         svs = svs *(i - 1)/i  + (mean - x)*(mean - x)/(i + 1);
         svsA = svsA *(i - 1)/i  + (meanA - y)*(meanA - y)/(i + 1);
         mean = mean + (x - mean)/(i+1);
         meanA = meanA + (y - meanA)/(i+1);
        
    }
    
    for(int i = 100;i < n;i++){
         u = ((double)rand()/(RAND_MAX));
         x = sqrt(1-u*u);
         y = x + copt*(u-0.5);
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
        auto Var = Control_u(N[i]);
        cout<<"The control variate is u, and N = "<<N[i]<<endl;
        cout<<"Value of crude MC estimator is "<<get<0>(Var)<<endl;
        cout<<"Value of control MC estimator is "<<get<1>(Var)<<endl;
        cout<<"Variance of crude MC estimator is "<<get<2>(Var)<<endl;
        cout<<"Variance of control MC estimator is "<<get<3>(Var)<<endl;
        cout<<endl;
    }
}