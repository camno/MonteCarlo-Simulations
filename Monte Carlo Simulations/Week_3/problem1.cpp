#include<iostream>
using namespace std;

//since the array is short, so we used a naive search method
bool isInArray(int a, int array[11]){ 
    if(array[a-2] == a){
        return true;
    }else{
        return false;
    }
}
int main(){
    double u1,u2 ; //u1,u2~u(0,1)
    int n1,n2; //n1,n2~{1,2,3,4,5,6}
    int N[5] = {100,1000,10000,100000,1000000};//array to store all iter. numbers
    int outcomes[11] = {2,3,4,5,6,7,8,9,10,11,12}; //array to store outcomes 
    int outComeSum;//indicator whether all possible outcomes are shown up
    int const maxSum = 77; // sum of all outcomes
    int counter = 0;
    int M = 0; 
    double ExpRollNum;

    for(int i=0;i<5;i=i+1){
        counter = 0 ;
        outComeSum = 0;
        M = 0;
        ExpRollNum = 0;
        for(int j=0;j<N[i];j=j+1){
            counter = counter + 1;
            u1 = ((double) rand() / (RAND_MAX));
            u2 = ((double) rand() / (RAND_MAX));
            n1 = (int)(u1 * 6.0) + 1 ;
            n2 = (int)(u2 * 6.0) + 1 ;
            //cout<<n1+n2<<endl;
            //if the sum of two dices have not shown before
            if( isInArray(n1+n2,outcomes)) { 
                outcomes[n1+n2-2] = 0; // set the tmp to be 0
                outComeSum = outComeSum + n1 + n2;
                //cout<<"at if "<<outComeSum<<endl;
                if(outComeSum == maxSum){ //all 11 possible outcomes are shown up 
                    ExpRollNum = ExpRollNum + counter;
                    M = M + 1;
                    counter = 0;
                    outComeSum = 0;
                    //reset outcome cases
                    for(int k= 0;k<11;k++){
                        outcomes[k] = k + 2;
                    }  
                }            
            }
        }
        if(M==0){
            cout<<"No occurence!"<<endl;
        }else{
            ExpRollNum = ((double) ExpRollNum)/M;
            cout<< "Expected dice rolls for N="<<N[i]<<" is "<< ExpRollNum << endl;
        }  
        //reset
        for(int k= 0;k<11;k++){
            outcomes[k] = k + 2;
        }
    }
} 
