#include<iostream>
#include<cmath>
using namespace std;

int busComing(){
    int numPassengers;//total number of passengers
    double t;//current time
    double u1,u2;//u(0,1),exp(15)
    t = 0;
    numPassengers = 0;
    while(t < 1.0){
        u1 = ((double)rand()/(RAND_MAX));
        u2 = ((double)rand()/(RAND_MAX));
        t = t - log(u1)/15;
        numPassengers = numPassengers + 20 + ((int) u2*21);
    }
    return numPassengers;
}

int main(){
    int N = 100000;
    int comer;
    double mean; //number of total arrivers in a hour
    int count;
    double prob;//prob. of total >500
    mean = 0;
    count = 0;
    srand(1);  //set up random seed
    for(int i = 0; i < N; i++)
    {
        comer = busComing();
        if (comer > 500) {
            count = count + 1;
        }
        mean =  mean + comer;
    } 
    prob = ((double) count / N);
    mean = mean / N;
    cout<<"Mean number of passengers arriving over a hour is "<<mean<<endl;
    cout<<"Probability of customers greater than 500 is "<<prob<<endl;
}