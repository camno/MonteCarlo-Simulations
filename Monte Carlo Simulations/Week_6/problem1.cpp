#include<iostream>
#include<cmath>
using namespace std;
double samVar(){
    int count=15; 
    int index;
    double u;     //u(0,1)
    double mean,mean2,samVar;
    double data[15]={5,4,9,6,21,17,11,20,7,12,21,15,13,16,8};

    mean = 0;
    mean2 = 0;
    for(int i = 0; i < count; i++)
    {
        u = ((double)rand()/(RAND_MAX));
        index = (int) (u*15);
        mean = mean + data[index];
        mean2 = mean2 + data[index]*data[index];
    }
    samVar = (mean2-mean*mean/15.0)/14.0;
    return samVar;
}

int main(){
    double theta,mean,mean2,variance;
    int count = 100000;
    srand(1) ;    // set up random seed

    mean = 0;
    mean2 = 0;
    for(int i = 0; i < count; i++)
    {
        theta = samVar();
        mean = mean + theta;
        mean2 = mean2 + theta*theta;
    }
    variance = (mean2 - mean*mean/count)/count;
    cout<<"Variance(S^2) is "<<variance<<endl;

}