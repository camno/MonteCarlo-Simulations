#include<iostream>
#include<cmath>
using namespace std;
int numGreatOne(){
    double u,sum;//u~(0,1), sum of us
    int i;
    sum = 0;
    i = 0;
    while( sum<= 1){
        u = ((double)rand()/(RAND_MAX));
        sum = sum + u;
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
        x = numGreatOne();
        mean = x;
        svs = 0;
        for(int i=1;i<N[j];i++){
            x = numGreatOne();
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