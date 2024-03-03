#include<iostream>
#include<cmath>
#include <tuple>
#define onethird 1.0/3.0
using namespace std;
/* The control variate is u, therefore x + c(u-0.5)*/
tuple<double,double,double,double> Control_uu2(int n){
    double u,us[100];  //u(0,1), 
    double x,y1,y2,u2,y; //x = sqrt(1-u^2),y1=u,y2=u*u
    double mean, svs;  //mean, sample variance of estimator
    double meanA,svsA; //mean, var of control
    double co_xy1,co_xy2,y1var,y1bar;//covariance, y mean, variance of y
    double y2var,y2bar,co_y1y2; 
    double xbar,c1opt,c2opt;

    u = ((double)rand()/(RAND_MAX));
    us[0] = u;
    y1 = u;
    y2 = u*u;
    x = sqrt(1-y2);
    xbar = x;

    y1bar = y1;
    y1var = 0;

    y2bar = y2;
    y2var = 0;

    co_xy1 = 0;
    co_xy2 = 0;
    co_y1y2 = 0;
    for(int i = 1; i < 100; i++)
    {
         u = ((double)rand()/(RAND_MAX));
         us[i] = u;
         y1 = u;
         y2 = u*u;
         x = sqrt(1-y2);
         y1var = y1var*(i - 1)/i  + (y1bar - y1)*(y1bar - y1)/(i + 1);
         y1bar = y1bar + (y1 - y1bar)/(i + 1);
         y2var = y2var*(i - 1)/i  + (y2bar - y2)*(y2bar - y2)/(i + 1);
         y2bar = y2bar + (y2 - y2bar)/(i + 1);

         xbar = xbar + (x - xbar)/(i + 1);
         co_xy1 = co_xy1*(i - 1)/i + (x-xbar)*(y1-y1bar)/i; //recursive covariance
         co_xy2 = co_xy2*(i - 1)/i + (x-xbar)*(y2-y2bar)/i; //recursive covariance
         co_y1y2 = co_y1y2*(i - 1)/i + (y1-y1bar)*(y2-y2bar)/i; //recursive covariance
    }
    c1opt = (co_xy2*co_y1y2-co_xy1*y2var)/( y2var*y1var - co_y1y2*co_y1y2); // c1_opt
    c2opt = (co_xy1*co_y1y2-co_xy2*y1var)/( y2var*y1var - co_y1y2*co_y1y2);//c2_opt

    u2 = us[0]*us[0];
    mean = sqrt(1-u2);
    meanA = mean + c1opt*(us[0]-0.5)+c2opt*(u2 - onethird); 
    svs = 0;
    svsA = 0;
    for(int i = 1; i < 100; i++)
    {
         u2 = us[i]*us[i];
         x = sqrt(1-u2);
         y = x + c1opt*(us[i]-0.5)+c2opt*(u2 - onethird); 
         svs = svs *(i - 1)/i  + (mean - x)*(mean - x)/(i + 1);
         svsA = svsA *(i - 1)/i  + (meanA - y)*(meanA - y)/(i + 1);
         mean = mean + (x - mean)/(i+1);
         meanA = meanA + (y - meanA)/(i+1);
        
    }
    
    for(int i = 100;i < n;i++){
         u = ((double)rand()/(RAND_MAX));
         u2 = u*u;
         x = sqrt(1-u2);
         y = x + c1opt*(u-0.5) + c2opt*(u2 - onethird); 
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
        auto Var = Control_uu2(N[i]);
        cout<<"The muilticontrol variate is u, and u^2, and N = "<<N[i]<<endl;
        cout<<"Value of crude MC estimator is "<<get<0>(Var)<<endl;
        cout<<"Value of control MC estimator is "<<get<1>(Var)<<endl;
        cout<<"Variance of crude MC estimator is "<<get<2>(Var)<<endl;
        cout<<"Variance of control MC estimator is "<<get<3>(Var)<<endl;
        cout<<endl;
    }
}