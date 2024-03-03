#include<iostream>
#include<cmath>
#define fgy 0.09/0.11
using namespace std;
//
// g(x)=1/10, f(x) is p_j, then c = 1.1 
// 
int main(){
    double u1,u2; //u~u(0,1)
    int x,y;//y is candidate, x is the acceptance
    int N[5] = {100,1000,10000,100000,1000000};//array to store all iter. numbers
    int counter[10] = {0}; //count the # of diff. ints
    int total_acceptance = 0;
    for(int i=0;i<5;i=i+1){

        for(int j = 0; j < N[i]; j++)
        {
            u1 = ((double)rand()/(RAND_MAX));
            y = (int)( u1*10.0 + 1.0);
            //f(y)=0.11 if y is odd, therefore f(y)/cg(y)=1,and u<1
            if ( y%2 == 1){ 
                x=y;
                counter[x-1] = counter[x-1] + 1;
                total_acceptance = total_acceptance + 1;
            }else{
                u2 = ((double)rand()/(RAND_MAX));
                if(u2<=fgy){
                    x=y;
                    counter[x-1] = counter[x-1] + 1;
                    total_acceptance = total_acceptance + 1;
                }
            }
        }
        cout<<"N= "<<N[i]<<" , total acceptace is "<<total_acceptance<<endl;
        for (int j=0;j<10;j++){
            cout<<"The probability of "<<(j+1)<<" is "<< (double)counter[j]/total_acceptance<<endl;
            counter[j] = 0; //reset
        }
        total_acceptance = 0;//reset
        cout<<"\n"<<endl;       
    }
}