#include<iostream>
#include<cmath>
#define pis 8.0*atan(1)
using namespace std;

double boxMuller(){
    double u1,u2,z;     //u(0,1),gsn(0,1)
    u1 = ((double)rand()/(RAND_MAX));
    u2 = ((double)rand()/(RAND_MAX));
    z = sqrt(-2*log(u1))*cos(pis*u2);
    return z;
}

int main(){
    double z;        //gsn(0,1)
    int count = 8;  //total walk steps
    double w[count+1]={0}; //positions
    double increase;
    double times[count+1] = {0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8};//time specified
    int N = 100000; //total number of Brownian Motion generated
    double mean[count]={0.0},mean2[count]={0.0},variance[count]={0.0};
    
    srand(1) ;  // set up random seed
    w[0] = 0.0; //initialize position
    for (int j=0; j<N; j++) {

        for(int i = 1; i <= count; i++)
        {
            z = boxMuller();
            increase = sqrt(times[i]-times[i-1])*z;
            w[i] = w[i-1] + increase;
            mean[i-1] = mean[i-1] + increase;
            mean2[i-1] = mean2[i-1] + increase*increase;
        }
    }
    for (int i = 0; i < count; i++) {
        variance[i] = (mean2[i] - mean[i]*mean[i]/N)/(N-1);
        mean[i] = mean[i]/N;
    }
    for(int i=0;i<count;i++){
    cout<<"The mean of increment of Brownian Motion is "<<mean[i]<<endl;
    cout<<"The variance of increment of Brownian Motion is "<<variance[i]<<endl;
    }
}
