#include<iostream>
#include<cmath>
#define pis 8*atan(1)//2
using namespace std;
double boxMuller(){
    double u1, u2;//u(0,1)
    double x, y;  //gsn(0,1)  
    u1 = ((double)rand()/(RAND_MAX));
    u2 = ((double)rand()/(RAND_MAX));
    x= sqrt(-2*log(u1))*cos(pis*u2);
    y= sqrt(-2*log(u1))*sin(pis*u2);
    return x;
}
int main(){
    double z[3];            // std gsn vector
    double x[3];            // multivariable gsn
    double mnVect[3]={0};   // estimate mean vector
    double ceMat[3][3]={0}; // estimate covariance matrix
    int N = 100000;        // total # of realization
    double A[3][3]={{2.0,0.0,0.0},{1.0,2.0,0},{0.5,1.25,0.433}};
    srand(1);              //set up the random seed
    for(int i=0;i<N;i++){
        //generate std gsn
        for(int j=0;j<3;j++){
            z[j]=boxMuller();
            x[j]=0;
        }
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                x[j] = x[j]+A[j][k]*z[k];
            }
            mnVect[j] = mnVect[j] + x[j]; //estimate mean vector
        }
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){       //estimate cov matrix
                ceMat[j][k] = ceMat[j][k] + x[j]*x[k];
            }
        }
    }
    for(int i=0;i<3;i++){
        mnVect[i] = mnVect[i]/N;
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            ceMat[i][j] = ceMat[i][j]/N - mnVect[i]*mnVect[j];
        }
    }
    cout<<"Total realization N = "<<N<<endl;
    cout<<"Estimate Mean Vector is [ ";
    for(int i=0;i<3;i++){
        cout<<mnVect[i]<<" ";
    }
    cout<<"]."<<"\n";
    cout<<"Estimate Covariance Matrix is "<<"\n";
    for(int j=0;j<3;j++){
        for(int k=0;k<3;k++){   
            cout<<ceMat[j][k]<<" ";
        }
        cout<<"\n";
    }
}