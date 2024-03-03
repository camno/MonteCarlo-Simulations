#include<iostream>
#include<cmath>
#include <tuple>
using namespace std;

double twoDices(){
    double u1,u2; //u1,u2~u(0,1)
    int n1,n2;     //n1~{1,2,3,4,5,6}
    int outcome;   //n1+n2
    int outComes[11]  = {2,3,4,5,6,7,8,9,10,11,12}; //outcomes
    int outComeSum;//indicator whether all possible outcomes are shown up
    int const maxSum = 77; // sum of all outcomes
    double i;//
    outComeSum = 0;
    i = 0;
    while((outComeSum != maxSum)){
        u1 = ((double) rand() / (RAND_MAX));
        u2 = ((double) rand() / (RAND_MAX));
        n1 = (int)(u1 * 6.0) + 1 ;
        n2 = (int)(u2 * 6.0) + 1 ;
        outcome = n1 + n2;     
        if( outcome == outComes[outcome-2]){
            outComes[outcome-2] = 0;
            outComeSum = outComeSum + outcome;
        }
        i = i + 1;
    }
    return i;
}

double twoDicesStrata(int I){
    double u1,u2; //u1,u2~u(0,1)
    int n1,n2;     //n1~{1,2,3,4,5,6}
    int outcome;   //n1+n2
    int outComes[11]  = {2,3,4,5,6,7,8,9,10,11,12}; //outcomes
    int outComeSum;//indicator whether all possible outcomes are shown up
    int const maxSum = 77; // sum of all outcomes
    double i;//

    outComeSum = I + 2;
    outComes[I] = 0;
    i = 1;
    while((outComeSum != maxSum)){
        u1 = ((double) rand() / (RAND_MAX));
        u2 = ((double) rand() / (RAND_MAX));
        n1 = (int)(u1 * 6.0) + 1 ;
        n2 = (int)(u2 * 6.0) + 1 ;
        outcome = n1 + n2;     
        if( outcome == outComes[outcome-2]){
            outComes[outcome-2] = 0;
            outComeSum = outComeSum + outcome;
        }
        i = i + 1;
    }
    return i;
}

tuple<double, double>estimator(){
    int n = 36000; // 11000 realizations to estimate
    int strata = 11;// 11 strata
    double x, xs[strata],xA;//Crude estimator, Stratified sampling estimator
    double est, estA, tmp;
    double ps[11] = {1.0/36,2.0/36,3.0/36,4.0/36,5.0/36,6.0/36,5.0/36,4.0/36,3.0/36,2.0/36,1.0/36};
    double ni[11] = {1000,2000,3000,4000,5000,6000,5000,4000,3000,2000,1000};//n*pi

    est = 0;  
    for(int i = 0; i < 10000; i++)
    {
        x = twoDices();
        est = est + (x-est)/(i+1);
    }
    estA = 0;
    for(int i = 0; i < strata; i++){
        tmp = 0;
        for(int j = 0; j < ni[i]; j++)// 1000 realization per strata
        { 
            xA = twoDicesStrata(i);
            tmp = tmp + (xA - tmp)/(j + 1);
        }
        estA = estA + tmp*ps[i];//since pi is the same, as pi=1/100
    }
    return make_tuple(est, estA);
}

tuple<double,double,double,double> getVars(int n){
    double u;          // u(0,1), 
    double x, xA;   // realizations
    double mean, svs;  //mean, sample variance of estimator
    double meanA,svsA; //mean, var of antithetic

    auto results = estimator();
    x = double(get<0>(results));
    xA = double(get<1>(results));
    mean = x;
    meanA = xA;
    svs = 0;
    svsA = 0; 
    for(int i = 1; i < n; i++)
    {
        auto results = estimator();
        x = double(get<0>(results));
        xA = double(get<1>(results));
        svs = svs *(i - 1)/i  + (mean - x)*(mean - x)/(i+1);
        mean = mean + (x-mean)/(i+1);
        svsA = svsA *(i - 1)/i  + (meanA - xA)*(meanA - xA)/(i+1);
        meanA = meanA + (xA-meanA)/(i+1);
    }
    return make_tuple(mean, meanA, svs, svsA);
}

int main(){
    int N = 100;    //generate 100 value of estimators
    srand(1);     //set up the same random seed for comparison
    auto Var = getVars(N);
    cout<<"For N = "<<N<<" realizations of estimators"<<endl;
    cout<<"Each estimator is generated from 36000 realizations"<<endl;
    cout<<"Mean Value of crude MC Estimator is "<<get<0>(Var)<<endl;
    cout<<"Mean Value of Stratified Sampling MC Estimator is "<<get<1>(Var)<<endl;
    cout<<"Variance of crude MC Estimator is "<<get<2>(Var)<<endl;
    cout<<"Variance of Stratified Sampling MC Estimator is "<<get<3>(Var)<<endl;
    cout<<endl;
}