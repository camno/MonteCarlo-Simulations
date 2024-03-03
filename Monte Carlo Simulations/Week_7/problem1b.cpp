#include<iostream>
#include<cmath>
#define pis 8.0*atan(1)
using namespace std;

double boxMuller(){
    double u1,u2,z;     //u(0,1),gsn(0,1)
    double w;
    u1 = ((double)rand()/(RAND_MAX));
    u2 = ((double)rand()/(RAND_MAX));
    z = sqrt(-2*log(u1))*cos(pis*u2);
    return z;
}
void swap(double *xp, double *yp) 
{ 
    double temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
// A function to implement bubble sort 
void bubbleSort(double arr[], double arr2[], int n) 
{ 
   int i, j; 
   for (i = 0; i < n-1; i++)       
  
       // Last i elements are already in place    
       for (j = 0; j < n-i-1; j++)  
           if (arr[j] > arr[j+1]) {
               swap(&arr[j], &arr[j+1]);
               swap(&arr2[j], &arr2[j+1]); 
           }
              
} 
int main(){
    double z;        //gsn(0,1)
    double wbegin = 0.0,tbegin = 0.0;
    double wend,tend = 0.8;
    double diffT, increase;
    int count = 4;
    double w[count+1] = {0,0}; //positions
    double t[count+1] = {0.0};//time
    double coVariance[count][count];//covariance of brownian positions
    double mean[count]={0},mean2[count]={0},variance[count]={0};
    int N = 100000,j; //total number of Brownian Motion generated
    
    srand(1) ;  // set up random seed
    for (int i=0; i<N; i++) {
        z = boxMuller();
        wend = wbegin + sqrt(tend-tbegin)*z; //end of the bridge
        w[0] = wbegin;
        w[1] = wend;
        t[0] = tbegin;
        t[1] = tend;
        diffT = tend - tbegin;
        j = 2;
        for(int j =2;j<count+1;j++){
            z = boxMuller();
            w[j] = 0.5*(w[j-1] + w[j-2]) + 0.5 * sqrt(diffT) * z;
            t[j] = 0.5*(t[j-1] + t[j-2]);
            diffT = abs(t[j]-t[j-1]);
        }
//================bubble sort====================
         bubbleSort(t, w , count+1);
//================================================
        for (int k = 0; k<count; k++) {
            increase = w[k+1] - w[k];
            mean[k] = mean[k] + increase;
            mean2[k] = mean2[k] + increase*increase;
        }
        
    }
    for (int i = 0; i < count; i++) {
        variance[i] = (mean2[i] - mean[i]*mean[i]/N)/(N-1);
        mean[i] = mean[i]/N;
    }
    for(int i=0;i<count;i++){
    cout<<"The mean of increment of Brownian Motion is "<<mean[i]<<endl;
    cout<<"The variance of increment of Brownian Motion is "<<variance[i]<<endl;
    }
}
