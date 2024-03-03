#include<iostream>
#define a 742938285  // Table 2.1 by Fishman,pg. 46 Monte Carlo Methods in Financial Engineering 2003
#define m 2147483647 // 2^31-1 
#define q 2          // q = [m/a]
#define r 661607077  // r =m mod a
using namespace std;

int linear_rand(int seed = 1)
{
    static int x = seed; //integer variable holding the current x_i
    int k; 
    k = x/q;
    x = a*(x-k*q)-k*r;
    if (x<0) {
        x=x+m;
    }
    return x ;
}

int main()
{
    double expectation,variance; // expectation, variance
    double x2_exp,rd,seed;             //squared expectation, tmp variable rd, and seed
    int N[6] = {10,100,1000,10000,100000,1000000};  //array to store all iter. numbers

    seed = 1;      //set up the random seed
    for(int i=0;i<6;i=i+1){

        expectation = 0;// initialize exp, squared x2, var
        x2_exp = 0;
        variance = 0;

        for(int j=0;j<N[i];j=j+1){
            rd = ((double) linear_rand(seed)/(m));
            x2_exp = x2_exp + rd*rd;
            expectation = expectation + rd;
        }
    
        expectation = expectation / N[i];//since exp is double. N[i] converts implicitly to double.
        x2_exp = x2_exp /N[i];
        variance = x2_exp - expectation * expectation;  // var = E(x2)-(E(x))2
        cout<< "E(x) estimation for N="<<N[i]<<" is "<< expectation << endl;
        cout<< "Var(x) estimation for N="<<N[i] <<" is "<< variance << endl;
        cout<<"\n";
    }
    return 0;
}