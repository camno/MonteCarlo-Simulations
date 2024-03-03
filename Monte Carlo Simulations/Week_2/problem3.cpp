#include<iostream>
#include<cmath>
#include<fstream>
using namespace std;
//acceptance - rejection, try g(x)=exp(-x);
//therefore, c=2(acceptable)
int main(){
    double u1,u2; //u~u(0,1)
    double temp; // f(y)/c*g(y)
    double x,y;//y is the candidate~exp(1), x is the acceptance
    int N = 1000000;//iter. numbers

    ofstream myfile;
    myfile.open("problem3.csv");
    for(int j = 0; j < N; j++){
        
        u1 = ((double)rand()/(RAND_MAX));
        u2 = ((double)rand()/(RAND_MAX));
        y = -log(u1);
        temp = y*exp(-y*y+y);
        if(u2<temp){
            x=y;
            myfile<<x<<"\n";
        }
    }
    myfile.close();
    return 0;

}