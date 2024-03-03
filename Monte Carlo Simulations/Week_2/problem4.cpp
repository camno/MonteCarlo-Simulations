#include<iostream>
#include<cmath>
#include<fstream>
using namespace std;
//acceptance - rejection, try g(x)=1/4,x in (2,6);
//therefore, C=2
int main(){
    double u1,u2; //u~u(0,1)
    double temp;  // f(y)/c*g(y)
    double x,y;   //y is the candidate~exp(1), x is the acceptance
    int N = 1000000;//iter. numbers

    ofstream myfile;
    myfile.open("problem4.csv");
    for(int j = 0; j < N; j++){     
        u1 = ((double)rand()/(RAND_MAX));
        u2 = ((double)rand()/(RAND_MAX));
        y = u1*4.0+2.0;//y in (2,6)
        if(y<3){
            temp = (y-2.0);
        }
        else{
            temp = 2.0 - y/3.0;
        }
        if(u2<temp){
            x=y;
            myfile<<x<<"\n";
        }    
    }
    myfile.close();
    return 0;
}