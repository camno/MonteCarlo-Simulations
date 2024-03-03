#include<iostream>
#include<cmath>
#include<fstream>
using namespace std;

int main(){
    // 50,and 100 strata for this experiment
    // 10, and 5 samples per strata accordingly
    double u,u_; //u~u(0,1)
    double p1[100]  = {0};//5 sample
    double p2[50] = {0};// 10 sample
    
    ofstream strata50;
    ofstream strata100;
    strata50.open("problem2a.csv");
    strata100.open("problem2b.csv");

    for(int i = 0; i < 100; i++)//equiprobable
    {
        p1[i] = ((double)0.01*i);   
    }

    for(int i = 0; i < 50; i++)
    {
        p2[i] = ((double)0.02*i);
    }
    for(int i = 0; i < 100; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            u = ((double)rand()/(RAND_MAX));
            u_ = 0.01 * u + p1[i];
            strata100 << -log(u_)<<"\n";
        }  
    }
    for(int i = 0; i < 50; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            u = ((double)rand()/(RAND_MAX));
            u_ = 0.02 * u + p2[i];
            strata50 << -log(u_) <<"\n";
        }  
    }
    strata100.close();
    strata50.close();
    return 0;
}