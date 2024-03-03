#include<iostream>
#include<cmath>
using namespace std;
double possionProcess(){
    double numCustmers;//total number of custmers
    double t;//current time
    double u1,u2;//u(0,1)
    double lambdat;
    t = 0;
    numCustmers = 0;
    while(t < 10.0){
        u1 = ((double)rand()/(RAND_MAX));
        t = t - log(u1)/7;
        if (t>10.0){
            break;
        }
        u2 = ((double)rand()/(RAND_MAX));
        lambdat = 3.0 + 4.0/(t+1.0);
        if (u2 < lambdat/7) {
            numCustmers = numCustmers + 1;
        }
    }
    return numCustmers;
}
int main(){
    int N = 100000;//total realizations
    double mean;
    double custmers; 
    srand(1);
    for(int i = 0; i < N; i++)
    {
        custmers = possionProcess();
        mean = mean + custmers;
    }
    mean = mean / N;
    cout<<"Mean Number of custmers arriving over ten hours is "<<mean<<endl;  
}