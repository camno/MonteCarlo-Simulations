#include<iostream>
#include<cmath>
#include<fstream>
#define C 2.0*exp(-0.5)
using namespace std;
//acceptance - rejection, try g(x)=0.5*exp(-0.5x);
//f(x) = 0.5(1+x)exp(-x), 0<x<inf
//therefore, c=1.2130(acceptable)
int main(){
    double u1,u2; //u~u(0,1)
    double temp; // f(y)/c*g(y)
    double x,y;//y is the candidate~exp(1), x is the acceptance
    int N = 1000000;//iter. numbers

    ofstream myfile;
    myfile.open("problem2.csv");
    for(int j = 0; j < N; j++){
        u1 = ((double)rand()/(RAND_MAX));
        u2 = ((double)rand()/(RAND_MAX));
        y = -log(u1)/0.5;
        temp = (1+y)*exp(-0.5*y)/C;
        if(u2<temp){
            x=y;
            myfile<<x<<"\n";
        }
    }
    myfile.close();
    return 0;
}