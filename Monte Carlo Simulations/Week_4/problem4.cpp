#include<iostream>
#include<cmath>
using namespace std;
int main(){
    int N=1000000;
    double u,x;         //u~u(0,1),exp(1)
    double integral;  //integration
    srand(1);         //set up the random seed
    integral = 0.0;
    for(int i=0;i<N;i++){
        u = ((double)rand()/(RAND_MAX));
        x = -log(u);
        integral = integral + exp(-pow(x,4.0) + x);
    }
    integral = integral * 2.0/ N;
    cout<<"The integration via Monte Carlo simulation is "<<integral<<endl;
}