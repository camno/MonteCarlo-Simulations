#include<iostream>
#include<cmath>
#include<chrono>
#include<fstream>
#define pis 8*atan(1)//2
#define an 6.0

using namespace std;
using namespace:: chrono;

//since the array is short, so we used a naive search method
int N = 1000000;//# of realization

void boxMuller(int n){
    double u1, u2;//u(0,1)
    double x, y;  //gsn(0,1)
    ofstream myfile;
    myfile.open("problem1a.csv");
    srand(1);     //set up the random seed
    for(int i= 0;i<n;i++){
        u1 = ((double)rand()/(RAND_MAX));
        u2 = ((double)rand()/(RAND_MAX));
        x= sqrt(-2*log(u1))*cos(pis*u2);
        y= sqrt(-2*log(u1))*sin(pis*u2);
        myfile<<x<<"\n";
    }
     myfile.close();
}
void appMethod(int n){
    double u,s,x; //u(0,1), sum of u, gaussian approximation
    int i;
    ofstream myfile;
    myfile.open("problem1b.csv");
    i = 0;
    srand(1);     //set up the random seed
    while(i < n){
        s = 0;    // initialize the sum
        for(int j=0;j<12;j++){
            u = ((double)rand()/(RAND_MAX));
            s = s + u;
        }
        x = s - an;
        myfile<<x<<"\n";
        i=i+1;
    }  
    myfile.close();
}
int main(){
    cout<<"N="<<N<<endl;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    boxMuller(N);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>( t2 - t1 ).count();
    cout<<"Box-Muller method needs "<<duration1<<" microseconds"<<endl;
    high_resolution_clock::time_point t3 = high_resolution_clock::now();
    appMethod(N);
    high_resolution_clock::time_point t4 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>( t4 - t3 ).count();
    cout<<"Approximate method needs "<<duration2<<" microseconds"<<endl;
    if(duration1<duration2){
        cout<<"Box-Muller method is more efficient!"<<endl;
    }else{
        cout<<"Approximate method is more efficient!"<<endl;
    }
    return 0;
}