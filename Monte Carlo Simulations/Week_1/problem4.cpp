#include<iostream>
#include<cmath>
using namespace std;

int main()
{
    double expectation, covariance; // expectation, covariance
    double eu, u_eu, rd, tmp;             //E(e^u), E(u*e^u), u=rd, tmp variable to hold e^u
    int N[6] = {10,100,1000,10000,100000,1000000};  //array to store all iter. numbers



    srand(1);                              //set up the random seed
    for(int i=0;i<6;i=i+1){

        expectation = 0;                  // initialize expectation, e^u , u*e^u, and covariance
        eu = 0;
        u_eu = 0;
        covariance = 0;

        for(int j=0;j<N[i];j=j+1){
            rd = ((double) rand() / (RAND_MAX));
            tmp = exp(rd);
            eu = eu + tmp;                           //sum e^u
            u_eu = u_eu + rd*tmp;                    // sum u*e^u
            expectation = expectation + rd;
        }
    
        expectation = expectation / N[i];            //since exp is double. N[i] converts implicitly to double.
        eu = eu /N[i];
        u_eu = u_eu /N[i];
        covariance = u_eu - expectation * eu;        // cov(xy) = E(xy)-E(x)E(y), where y=e^u
        cout<< "E(u) estimation for N="<<N[i]<<" is "<< expectation << endl;
        cout<< "Cov(u,e^u) estimation for N="<<N[i] <<" is "<< covariance << endl;
        cout<<"\n";
    }
    return 0;
}