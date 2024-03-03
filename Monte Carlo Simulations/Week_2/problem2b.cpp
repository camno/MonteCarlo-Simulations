#include<iostream>
using namespace std;
int main(){
    double u1; //u~u(0,1)
    int N[5] = {100,1000,10000,100000,1000000};//array to store all iter. #s
    int counter[10] = {0}; //count the # of diff. ints

    for(int i=0;i<5;i=i+1){
        for(int j = 0; j < N[i]; j++)
        {
            u1 = ((double)rand()/(RAND_MAX));
            if (u1<=0.11){
                counter[0] = counter[0] + 1; 
            }else if(u1<=0.2){
                counter[1] = counter[1] + 1; 
            }else if(u1<=0.31){
                counter[2] = counter[2] + 1; 
            }else if(u1<=0.4){
                counter[3] = counter[3] + 1; 
            }else if(u1<=0.51){
                counter[4] = counter[4] + 1; 
            }else if(u1<=0.6){
                counter[5] = counter[5] + 1; 
            }else if(u1<=0.71){
                counter[6] = counter[6] + 1; 
            }else if(u1<=0.8){
                counter[7] = counter[7] + 1; 
            }else if(u1<=0.91){
                counter[8] = counter[8] + 1; 
            }else {
                counter[9] = counter[9] + 1; 
            }
        }
        cout<<"N="<<N[i]<<endl;
        for (int j=0;j<10;j++){
            cout<<"The probability of "<<(j+1)<<" is "<< (double)counter[j]/N[i]<<endl;
            counter[j] = 0;   //reset
        }
        cout<<"\n"<<endl;       
    }
}