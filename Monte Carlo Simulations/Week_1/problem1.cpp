#include<iostream>
using namespace std;

int main()
{
    double expectation,variance; // expectation, variance
    double x2_exp,rd;             //squared expectation, tmp variable rd
    int N[6] = {10,100,1000,10000,100000,1000000};  //array to store all iter. numbers

    srand(1);      //set up the random seed
    for(int i=0;i<6;i=i+1){

        expectation = 0;// initialize exp, squared x2, var
        x2_exp = 0;
        variance = 0;
        
        for(int j=0;j<N[i];j=j+1){
            rd = ((double) rand() / (RAND_MAX));
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