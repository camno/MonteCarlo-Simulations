#include<iostream>
#include<cmath>
#define pis 8*atan(1)//2pi
using namespace std;

double boxMuller(){
    double u1, u2;//u(0,1)
    double x, y;  //gsn(0,1)  
    double tmp,tmp2;
    u1 = ((double)rand()/(RAND_MAX));
    u2 = ((double)rand()/(RAND_MAX));
    tmp = sqrt(-2*log(u1));
    tmp2 = pis*u2;
    x = tmp * cos(tmp2);
    y = tmp * sin(tmp2);
    return x;
}

int main(){
    int i; // counter realizations
    double tol;    // S/sqrt(N)
    double z, mean, svs;// gsn(0,1), mean, sample variance

    srand(1) ;    // set up random seed
    z = boxMuller();
    mean = z;
    svs = 0;
    i = 1;
    tol = 10;   //initialize error
    while(tol >= 0.0001 ){
        z = boxMuller();
        svs = svs *(i - 1)/i  + (mean - z)*(mean - z)/(i+1);
        mean = mean + (z-mean)/(i+1);
        i = i + 1;
        tol = svs/i;
    }
    cout << "Total Gaussian generated: "<< i << endl;
    cout << "Sample mean is " << mean << endl;
    cout << "Sample variance is " << svs << endl;
}