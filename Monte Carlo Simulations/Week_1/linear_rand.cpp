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
int main(){
    for(int i=0;i<10;i++)
    cout<<linear_rand(2)<<endl;
    return 0;
}