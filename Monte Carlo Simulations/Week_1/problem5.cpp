#include<iostream>
using namespace std;

int main()
{
    double E_M, M, sum_u; // variable : E(M), M
    double u;             // u~u(0,1)
    int N[6] = {100,1000,10000,100000,1000000};  //array to store all iter. numbers
    int counter ;          //count the number of occurence that the sum exceeds 1
     
    srand(1);      //set up the random seed
    for(int i=0;i<5;i=i+1){

        M       = 0;     // initialize E(M), M, sum u, counter
        E_M     = 0;
        sum_u   = 0;
        counter = 0;
        for(int j=0;j<N[i];j=j+1){
            if (sum_u <= 1.0) {
                u = ((double) rand() / (RAND_MAX));
                sum_u = sum_u + u;
                M = M + 1;  
            }else{
                E_M = E_M + M ;
                counter = counter + 1;
                sum_u = ((double) rand() / (RAND_MAX)); //restart a summation since the sum exceeds 1
                M = 1;
            }
        }
        if(counter == 0){
            cout<<"No occurence"<<endl;
        }else{
            E_M = E_M / counter;        //since E_M is double. counter converts implicitly to double.
        }   
        cout<< "E(M) estimation for N="<< N[i] <<" is "<< E_M << endl;
        cout<<"\n";
    }
    return 0;
}
