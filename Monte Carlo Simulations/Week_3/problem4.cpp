#include<iostream>
#include<cmath>
#include<chrono>
#define pis 8*atan(1)//2

using namespace std;
using namespace:: chrono;

int N = 10000000;//# of realization
void boxMuller(int n){
    double u1, u2;//u(0,1)
    double x, y; //gsn(0,1)
    for(int i= 0;i<n;i++){
        u1 = ((double)rand()/(RAND_MAX));
        u2 = ((double)rand()/(RAND_MAX));
        x= sqrt(-2*log(u1))*cos(pis*u2);
        y= sqrt(-2*log(u1))*sin(pis*u2);
    }
}
void marsaglia(int n){
    double u1, u2;//u(0,1)
    double v1,v2;//u(-1,1)
    double s,z;
    double x, y; //gsn(0,1)
    for(int i= 0;i<n;i++){
        u1 = ((double)rand()/(RAND_MAX));
        u2 = ((double)rand()/(RAND_MAX));
        v1 = 2*u1 - 1;
        v2 = 2*u2 - 1;
        s = v1*v1 + v2*v2;
        if(s<=1.0){
            z = sqrt(-2*log(s)/s);
            x = z*v1;
            y = z*v2;
        }
    }
}
int main(){
    cout<<"N="<<N<<endl;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    boxMuller(N);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>( t2 - t1 ).count();
    cout<<"Box-Muller method needs "<<duration1<<" microseconds"<<endl;
    high_resolution_clock::time_point t3 = high_resolution_clock::now();
    marsaglia(N);
    high_resolution_clock::time_point t4 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>( t4 - t3 ).count();
    cout<<"Marsaglias method needs "<<duration2<<" microseconds"<<endl;
    if(duration1<duration2){
        cout<<"Box-Muller method is more efficient!"<<endl;
    }else{
        cout<<"Marsaglias method is more efficient!"<<endl;
    }
    return 0;
}