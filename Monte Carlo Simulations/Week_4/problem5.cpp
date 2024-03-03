#include<iostream>
#include<cmath>
using namespace std;
int main(){
    int N = 1000000;
    double u1,u2;     //u1~u(0,2),u2~u(0,3)
    double integral;  //integration
    srand(1);         //set up the random seed
    integral = 0.0;
    for(int i=0;i<N;i++){
        u1 = ((double)rand()/(RAND_MAX))*2.0;
        u2 = ((double)rand()/(RAND_MAX))*3.0;
        integral = integral + exp((u1+u2)*(u1+u2));
    }
    integral = integral * 6.0/ N;
    cout<<"The integration via Monte Carlo simulation is "<<integral<<endl;
}