#include<iostream>
#include<cmath>
#include <tuple>
using namespace std;

tuple<double,double> twoDices(){
    double u1,u2,u1A,u2A ; //u1,u2~u(0,1)
    int n1,n2,n1A,n2A;     //n1,n2~{1,2,3,4,5,6}
    int outcome,outcomeA;   //n1+n2, n1A+n2A
    int outComes[11]  = {2,3,4,5,6,7,8,9,10,11,12}; //outcomes
    int outComesA[11] = {2,3,4,5,6,7,8,9,10,11,12}; //outcomes
    int outComeSum,outComeSumA;//indicator whether all possible outcomes are shown up
    int const maxSum = 77; // sum of all outcomes
    double i,j;

    outComeSum = 0;
    i = 0;
    outComeSumA = 0;
    j = 0;
    while((outComeSum != maxSum) ||(outComeSumA != maxSum)){
        
        u1 = ((double) rand() / (RAND_MAX));
        u2 = ((double) rand() / (RAND_MAX));
        u1A = 1 - u1;
        u2A = 1 - u2;

        n1 = (int)(u1 * 6.0) + 1 ;
        n2 = (int)(u2 * 6.0) + 1 ;
        n1A = (int)(u1A * 6.0) + 1 ;
        n2A = (int)(u2A * 6.0) + 1 ;

        outcome = n1 + n2;
        outcomeA = n1A + n2A;

        if (outComeSum != maxSum) {
            if( outcome == outComes[outcome-2]){
                outComes[outcome-2] = 0;
                outComeSum = outComeSum + outcome;
            }
            i = i + 1;
        }

        if (outComeSumA != maxSum) {
            if( outcome == outComesA[outcome-2]){
                outComesA[outcome-2] = 0;
                outComeSumA = outComeSumA + outcome;
            }
            j = j + 1;
        }

        if (outComeSumA != maxSum) {
            if( outcomeA == outComesA[outcomeA-2]){
                outComesA[outcomeA-2] = 0;
                outComeSumA = outComeSumA + outcomeA;
            }
            j = j + 1;
        }
    }
    return make_tuple(i,j);
}
tuple<double,double,double,double> getVars(int n){ 
    double x, y, xA;   // realizations
    double mean, svs;  //mean, sample variance of estimator
    double meanA,svsA; //mean, var of antithetic

    auto results = twoDices();
    x = get<0>(results);
    y = get<1>(results);
    xA = y;     //(x+y)/2;
    mean = x;
    meanA = xA;
    svs = 0;
    svsA = 0;
    for(int i = 1; i < n; i++)
    {
        auto results = twoDices();
        x = double(get<0>(results));
        y = double(get<1>(results));
        xA = (x+y)/2;
        svs = svs *(i - 1)/i  + (mean - x)*(mean - x)/(i+1);
        mean = mean + (x-mean)/(i+1);

        svsA = svsA *(i - 1)/i  + (meanA - xA)*(meanA - xA)/(i+1);
        meanA = meanA + (xA-meanA)/(i+1);
    }
    return make_tuple(mean, meanA, svs, svsA);
}

int main(){
    int N[5]={100,1000,10000,100000,1000000};
    for(int i=0;i<5;i++){
        srand(1);       //set up the same random seed for comparison
        auto Var = getVars(N[i]);
        cout<<"For N = "<<N[i]<<endl;
        cout<<"Value of the estimate is "<<get<0>(Var)<<endl;
        cout<<"Value of antithetic estimate is "<<get<1>(Var)<<endl;
        cout<<"Variance of normal estimate is "<<get<2>(Var)<<endl;
        cout<<"Variance of antithetic estimate is "<<get<3>(Var)<<endl;
        cout<<endl;
    }
}