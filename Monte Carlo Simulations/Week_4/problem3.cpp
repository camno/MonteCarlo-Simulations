#include<iostream>
#include<cmath>
#define oneThird 1.0/3.0
using namespace std;
int main(){
    int N=100000;
    double u;         //u~u(0,1)
    double integral;  //integration
    srand(1);         //set up the random seed
    integral = 0.0;
    for(int i=0;i<N;i++){
        u = ((double)rand()/(RAND_MAX));
        integral = integral + pow(u/(1-u),oneThird); 
    }
    integral = integral * oneThird / N;
    cout<<"The integration via Monte Carlo simulation is "<<integral<<endl;
}