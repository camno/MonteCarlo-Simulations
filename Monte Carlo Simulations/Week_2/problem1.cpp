#include<iostream>
#include<cmath>
#define half_pi 2.0*atan(1)
#define pi 4.0*atan(1)
using namespace std;

// Use acceptance and rejection method
// consider 2 random numbers u1, u2; u1 determines one end of the rod;
// the rotatition of the rod, theta, is determined by the u2, 
// due to symmetry, (o,half pi) is considered
// if u1 plus/minus the projection of the rod is >/< 1, 
// then the rod crossed the line

int main(){
    double u1, u2 ; //u1,u2~u(0,1)
    double theta; //angle of the rod, theta~u(-pi/2,pi/2)
    int N[5] = {100,1000,10000,100000,1000000};//array to store all iter. numbers
    int counter;
    double prob;
    for(int i=0;i<5;i=i+1){
        counter = 0 ;
        for(int j=0;j<N[i];j=j+1){
            u1 = ((double) rand() / (RAND_MAX));
            u2 = ((double) rand() / (RAND_MAX));
            u1 = u1 * 0.5;
            theta = u2 * pi - half_pi; 
            if( u1 + 0.5*sin(theta)> 0.50){
                counter = counter + 1;}
        }
        prob = ((double) counter)/N[i];
        cout<< "Crossing probability for N="<<N[i]<<" is "<< prob << endl;

    }
} 