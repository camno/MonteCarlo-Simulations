#include<iostream>
#include<cmath>
#include <tuple>
using namespace std;

tuple<double,double> twoDices(){
    double u1,u2; //u1,u2~u(0,1)
    int n1,n2;     //n1~{1,2,3,4,5,6}
    int outcome;   //n1+n2
    int outComes[11]  = {2,3,4,5,6,7,8,9,10,11,12}; //outcomes
    int outComeSum;//indicator whether all possible outcomes are shown up
    int const maxSum = 77; // sum of all outcomes
    double i,j,k;//j is the control variate

    outComeSum = 0;
    i = 0;
    j = 0;
    k = 0;
    while((outComeSum != maxSum)){
        u1 = ((double) rand() / (RAND_MAX));
        u2 = ((double) rand() / (RAND_MAX));
        n1 = (int)(u1 * 6.0) + 1 ;
        n2 = (int)(u2 * 6.0) + 1 ;
        outcome = n1 + n2;

        if( (outcome == 2 )&&(j==0)){
            j = i + 1;
        }
        if( (outcome == 12 )&&(k==0)){
            k = i + 1;
        }
        if( outcome == outComes[outcome-2]){
            outComes[outcome-2] = 0;
            outComeSum = outComeSum + outcome;
        }
        i = i + 1;
    }
    j = j + k;
    return make_tuple(i,j);
}
tuple<double,double,double,double> getVars(int n){
    double u, copt;          // u(0,1), 
    double x, xs[100], y, ys[100], xA;   // realizations
    double xbar,ybar,yvar,co_xy;
    double mean, svs;  //mean, sample variance of estimator
    double meanA,svsA; //mean, var of antithetic

    auto results = twoDices();
    x = get<0>(results);
    xs[0] = x;
    y = get<1>(results);
    ys[0] = y;

    xbar = x;
    ybar = y;
    yvar = 0;
    co_xy = 0;
    for(int i = 1; i < 100; i++)
    {
         auto results = twoDices();
         x = get<0>(results);
         y = get<1>(results);
         xs[i] = x;
         ys[i] = y;
         yvar = yvar*(i - 1)/i  + (ybar - y)*(ybar - y)/(i + 1);
         ybar = ybar + (y - ybar)/(i + 1);
         xbar = xbar + (x - xbar)/(i + 1);
         co_xy = co_xy*i/(i+1) + (x-xbar)*(y-ybar)/(i+1); //recursive covariance
    }
    copt = -co_xy/yvar; // c_opt
    
    x = xs[0];
    y = ys[0];
    xA = x + copt*(y-72);
    mean = x;
    meanA = xA;
    svs = 0;
    svsA = 0;

    for(int i = 1; i < 100; i++)
    {
        x = xs[i];
        y = ys[i];
        xA = x + copt*(y-72);
        svs = svs *(i - 1)/i  + (mean - x)*(mean - x)/(i+1);
        mean = mean + (x-mean)/(i+1);
        svsA = svsA *(i - 1)/i  + (meanA - xA)*(meanA - xA)/(i+1);
        meanA = meanA + (xA-meanA)/(i+1);
    }
    
    for(int i = 100; i < n; i++)
    {
        auto results = twoDices();
        x = double(get<0>(results));
        y = double(get<1>(results));
        xA = x + copt*(y-72);
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
        cout<<"Value of the crude M is "<<get<0>(Var)<<endl;
        cout<<"Value of Control M is "<<get<1>(Var)<<endl;
        cout<<"Variance of the crude M is "<<get<2>(Var)<<endl;
        cout<<"Variance of Control M is "<<get<3>(Var)<<endl;
        cout<<endl;
    }
}