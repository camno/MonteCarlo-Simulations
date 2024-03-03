#include<iostream>
#include<cmath>
#include <tuple>
using namespace std;
double numGreatOne(){
    double u,sum;//u~(0,1), sum of us, sum of antithetics
    double i;
    u = ((double)rand()/(RAND_MAX));
    i = 1;
    sum = u;
    while( (sum<= 1) ){
        u = ((double)rand()/(RAND_MAX));
        sum = sum + u;
        i = i + 1;
    }
    return i;
}
double numGreatOneStrata(int I, int N){
    double u,u_,sum;//u~(0,1), sum of us, sum of antithetics
    double i;
    u = ((double)rand()/(RAND_MAX));
    u_ = ((double)(u + I)/N);
    i = 1;
    sum = u_;
    while(sum<=1){
        u = ((double)rand()/(RAND_MAX));
        sum = sum + u;
        i = i + 1;
    }
    return i;
}
tuple<double, double>estimator(){
    int n = 10000; // 10000 realizations to estimate
    int strata = 100;// 100 strata
    double x, xs[strata],xA;//Crude estimator, Stratified sampling estimator
    double est, estA,tmp;

    est = 0;
    estA = 0;
    for(int i = 0; i < 10000; i++)
    {
        x = numGreatOne();
        est = est + (x-est)/(i+1);
    }

    for(int i = 0; i < strata; i++){
        tmp = 0;
        for(int j = 0; j < 100; j++)// 100 realization per strata
        { 
            xA = numGreatOneStrata(i,strata);
            tmp = tmp + (xA-tmp)/(j+1);
        }
        estA = estA + (tmp - estA)/(i + 1);//since pi is the same, as pi=1/100
    }
    return make_tuple(est,estA);
}

tuple<double,double,double,double> getVars(int n){
    double u;          // u(0,1), 
    double x, y, xA;   // realizations
    double mean, svs;  //mean, sample variance of estimator
    double meanA,svsA; //mean, var of antithetic

    auto results = estimator();
    x = double(get<0>(results));
    y = double(get<1>(results));
    xA = y;
    mean = x;
    meanA = xA;
    svs = 0;
    svsA = 0; 
    for(int i = 1; i < n; i++)
    {
        auto results = estimator();
        x = double(get<0>(results));
        y = double(get<1>(results));
        xA = y;
        svs = svs *(i - 1)/i  + (mean - x)*(mean - x)/(i+1);
        mean = mean + (x-mean)/(i+1);
        svsA = svsA *(i - 1)/i  + (meanA - xA)*(meanA - xA)/(i+1);
        meanA = meanA + (xA-meanA)/(i+ 1);
    }
    return make_tuple(mean, meanA, svs, svsA);
}

int main(){
    int N=100; //generate 100 estimator
    srand(1);       //set up the same random seed for comparison
    auto Var = getVars(N);
    cout<<"For N = "<<N<<endl;
    cout<<"Mean Value of crude MC Estimator is "<<get<0>(Var)<<endl;
    cout<<"Mean Value of Stratified Sampling MC Estimator is "<<get<1>(Var)<<endl;
    cout<<"Variance of crude MC Estimator is "<<get<2>(Var)<<endl;
    cout<<"Variance of Stratified Sampling MC Estimator is "<<get<3>(Var)<<endl;
    cout<<endl;
}