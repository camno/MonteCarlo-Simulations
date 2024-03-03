#include<iostream>
#include<cmath>
using namespace std;
int twoDices(){
    double u1,u2 ; //u1,u2~u(0,1)
    int n1,n2;     //n1,n2~{1,2,3,4,5,6}
    int outcome;   //n1+n2
    int outComes[11] = {2,3,4,5,6,7,8,9,10,11,12}; //outcomes
    int outComeSum;//indicator whether all possible outcomes are shown up
    int const maxSum = 77; // sum of all outcomes
    int i;

    outComeSum = 0;
    i = 0;
    while(outComeSum != maxSum){
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
int main(){
    int N[5] = {100,1000,10000,100000,1000000}; 
    double x;          //realization
    double mean, svs;  //mean, sample variance of estimator
    double std, Nsqrt; // standard deviation
    double l_bound, u_bound;
    srand(3);          //set up the random seed
    for(int j=0;j<5;j++){
        x = twoDices();
        mean = x;
        svs = 0;
        for(int i=1;i<N[j];i++){
            x = twoDices();
            svs = svs *(i - 1)/i  + (mean - x)*(mean - x)/(i+1);
            mean = mean + (x-mean)/(i+1);
        }
        std = sqrt(svs);
        Nsqrt = sqrt(N[j]);
        l_bound = mean - std * 1.96/Nsqrt;
        u_bound = mean + std * 1.96/Nsqrt;
        cout<<"Total realization is "<< N[j] <<endl;
        cout<<"The estimator is "<<mean<<endl;
        cout<<"The 95 percent confidence intervals is "<<endl;
        cout<<"["<< l_bound<<" , "<<u_bound<<"]"<<"\n"<<endl;
    }
}