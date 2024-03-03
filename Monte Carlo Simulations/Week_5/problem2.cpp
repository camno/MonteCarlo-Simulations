#include<iostream>
#include<cmath>
using namespace std;
int main(){
    int i; // counter realizations
    double u;          // u(0,1), 
    double x;          //realization of exp(u^2)
    double est;        // estimator(integral)
    double mean, svs;  //mean, sample variance of estimator
    srand(1);          //set up the random seed
    u = ((double)rand()/(RAND_MAX));
    x = exp(u*u);
    est = x ;
    svs = 0;
    mean = est;
    i = 1;
    while(svs >=0.000001 || i<100){
        u = ((double)rand()/(RAND_MAX));
        x = exp(u*u);
        est = est + (x - est)/(i+1);
        svs = svs *(i - 1)/i  + (mean - est)*(mean - est)/(i + 1);
        mean = mean + (est - mean)/(i+1);
        i = i + 1;
    }
    cout<<"Total realization is "<<i<<endl;
    cout<<"The integration via Monte Carlo simulation is "<< est <<endl;
}
