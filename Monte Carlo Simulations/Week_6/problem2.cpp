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
double samMean(int data[1000]){
    int count=1000; 
    int index;
    double u;     //u(0,1)
    double mean;

    mean = 0;
    for(int i = 0; i < count; i++)
    {
        u = ((double)rand()/(RAND_MAX));
        index = (int) (u*1000);
        mean = mean + data[index];
    }
    mean = mean /count;
    return mean;
}

 int main(){
     double x;          //realization
     double mean, mean2, variance;  //mean, variance of estimator
     int count = 1000;
     int data[count];  //store generated data
     srand(1);// set up random seed

     for(int i = 0; i < count; i++)
     {
        data[i] = twoDices();
     }
     mean = 0;
     mean2 = 0;
     for(int i = 0; i < count; i++)
     {
         x = samMean(data);
         mean = mean + x;
         mean2 = mean2 + x*x;
     }
    variance = (mean2 - mean*mean/count)/(count-1);
    cout<<"Variance is "<<variance<<endl;
 }