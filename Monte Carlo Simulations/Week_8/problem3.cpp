#include<iostream>
#include<cmath>
#include <tuple>
#define onethird 1.0/3.0
using namespace std;
tuple<double,double> numGreatOne(){
    double u,sum,sumA;//u~(0,1), sum of us, sum of antithetics
    double i,j;
    u = ((double)rand()/(RAND_MAX));
    sum = u;
    u = ((double)rand()/(RAND_MAX));
    sum = sum + u;
    j = sum;
    i = 2;
    while( (sum<= 1) ){
        u = ((double)rand()/(RAND_MAX));
        sum = sum + u;
        i = i + 1;
    }
    return make_tuple(i,j);
}
tuple<double,double,double,double> getVars(int n){
    double u, copt;          // u(0,1), 
    double x, xs[100], y, ys[100], xA;   // realizations
    double xbar,ybar,yvar,co_xy;
    double mean, svs;  //mean, sample variance of estimator
    double meanA,svsA; //mean, var of antithetic

    auto results = numGreatOne();
    x = get<0>(results);
    xs[0] = x;
    y = get<1>(results);
    ys[0]= y;

    xbar = x;
    ybar = y;
    yvar = 0;
    co_xy = 0;
    for(int i = 1; i < 100; i++)
    {
         auto results = numGreatOne();
         x = get<0>(results);
         y = get<1>(results);
         xs[i] = x;
         ys[i] = y;
         yvar = yvar*(i - 1)/i  + (ybar - y)*(ybar - y)/(i + 1);
         ybar = ybar + (y - ybar)/(i + 1);
         xbar = xbar + (x - xbar)/(i + 1);
         co_xy = co_xy* i/(i+1) + (x-xbar)*(y-ybar)/(i+1); //recursive covariance
    }
    copt = -co_xy/yvar; // c_opt
    
    x = xs[0];
    y = ys[0];
    xA = x + copt*(y-1);
    mean = x;
    meanA = xA;
    svs = 0;
    svsA = 0;
    for(int i = 1; i < 100; i++)
    {
        x = xs[i];
        y = ys[i];
        xA = x + copt*(y-1);
        svs = svs *(i - 1)/i  + (mean - x)*(mean - x)/(i+1);
        mean = mean + (x-mean)/(i+1);

        svsA = svsA *(i - 1)/i  + (meanA - xA)*(meanA - xA)/(i+1);
        meanA = meanA + (xA-meanA)/(i+1);
        
    }
    
    for(int i = 100; i < n; i++)
    {
        auto results = numGreatOne();
        x = double(get<0>(results));
        y = double(get<1>(results));
        xA = x + copt*(y-1);
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
        cout<<"Value of Control M is "<<get<1>(Var)<<endl;
        cout<<"Variance of normal M is "<<get<2>(Var)<<endl;
        cout<<"Variance of Control M is "<<get<3>(Var)<<endl;
        cout<<endl;
    }
}