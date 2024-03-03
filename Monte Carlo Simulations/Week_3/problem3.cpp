#include<iostream>
#include<cmath>
#include<fstream>
#define C 1.875
using namespace std;
//acceptance - rejection, try g(x)=1;
//f(x) = 30*(x^2-2x^3+x^4), 0<x<1
//therefore, c=1.875(acceptable)
int main(){
    double u1,u2; //u~u(0,1)
    double temp; // f(y)/c*g(y)
    double x,y,y2,y3;//y is the candidate, x is the acceptance
    int N = 1000000;//iter. numbers

    ofstream myfile;
    myfile.open("problem3.csv");
    for(int j = 0; j < N; j++){
        
        u1 = ((double)rand()/(RAND_MAX));
        u2 = ((double)rand()/(RAND_MAX));
        y = u1;
        y2 = y*y;
        y3 = y2*y;
        temp = 30.0*(y2-2*y3+y3*y)/C;
        if(u2<temp){
            x=y;
            myfile<<x<<"\n";
        }
    }
    myfile.close();
    return 0;
}