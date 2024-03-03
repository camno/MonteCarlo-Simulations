#include<iostream>
#include<cmath>
#include <tuple>
#define coef1 25.0/12.0
using namespace std;

tuple<double,double,double,double,double> twoNumbers(){
    double u1,u2; //u1,u2~u(0,1)
    double e1,e2,s; //exp(1),exp(0.5)
    double i,j,ii,jj;//i crude, j is the control variate, ii antithetic, jj importance sampling
    double jjj;//jjj importance sampling on conditioning
    
    //importance sampling: g(x) is tilted distribution with t = 0.2
    u1 = ((double)rand()/(RAND_MAX));
    u2 = ((double)rand()/(RAND_MAX));
    e1 = -log(u1);
    e2 = -2*log(u2);
    i = 0;
    j = 0;
    ii = 0;
    jj = 0;
 // crude
    if ((e1+e2>4)) {
        i = 1.0;
    }
//conditioning
    if (e2>=4.0) {
        j = 1.0;
    }else{
        j = exp(e2 - 4.0);
    }
 // antithetic, later averaged
    if (-log(1-u1)-2*log(1-u2)>4) {
        ii = 1.0;
    }
// importance sampling, using tilted distribution with t=0.2
    e1 =  -5.0/4.0 * log(u1);
    e2 = -10.0/3.0 * log(u2);
    
    s = e1 + e2;
    if(s >=4){
        jj = exp(-0.2*s)*25/12.0;
    }
//importance sampling on conditional estimator
    if (e2 >= 4.0) {
        jjj = exp(-0.2*s)*25/12.0;
    }else{
        jjj = exp(e2 - 4.0) * exp(-0.2*s)*25/12.0;
    }
    
    return make_tuple(i,j,ii,jj,jjj);
}
tuple<double,double,double,double,double,double,double,double,double,double> getVars(int n){
    double x, y, xA, xB, xC,xD;   // realizations
    double y1,y2,y3;
    double mean, svs;  //mean, sample variance of estimator
    double meanA,svsA; //mean, var of conditioning
    double meanB,svsB; //mean, var of antithetic
    double meanC,svsC; //mean, var of importance sampling
    double meanD,svsD; //mean, var of importance sampling on conditioning

    auto results = twoNumbers();
    x = get<0>(results);
    y = get<1>(results);
    y1 = get<2>(results);
    y2 = get<3>(results);
    y3 = get<4>(results);
    
    xA = y;
    xB = (x + y1)/2.0;
    xC = y2;
    
    mean = x;
    meanA = xA;
    meanB = xB;
    meanC = xC;
    meanD = xD;
    
    svs = 0;
    svsA = 0;
    svsB = 0;
    svsC = 0;
    for(int i = 1; i < n; i++)
    {
        auto results = twoNumbers();
        x =  get<0>(results);
        y =  get<1>(results);
        y1 = get<2>(results);
        y2 = get<3>(results);
        y3 = get<3>(results);
        
        xA = y;
        xB = (x + y1)/2.0;
        xC = y2;
        xD = y3;
        
        svs = svs *(i - 1)/i  + (mean - x)*(mean - x)/(i+1);
        mean = mean + (x-mean)/(i+1);

        svsA = svsA *(i - 1)/i  + (meanA - xA)*(meanA - xA)/(i+1);
        meanA = meanA + (xA-meanA)/(i+1);
        
        svsB = svsB *(i - 1)/i  + (meanB - xB)*(meanB - xB)/(i+1);
        meanB = meanB + (xB-meanB)/(i+1);
        
        svsC = svsC *(i - 1)/i  + (meanC - xC)*(meanC - xC)/(i+1);
        meanC = meanC + (xC-meanC)/(i+1);
        
        svsD = svsD *(i - 1)/i  + (meanD - xD)*(meanD - xD)/(i+1);
        meanD = meanD + (xD-meanD)/(i+1);
    }
    return make_tuple(mean, meanA, meanB, meanC, meanD, svs, svsA, svsB,svsC,svsD);
}

int main(){
    int N = 1000;
    srand(5);       //set up the same random seed for comparison
    auto Var = getVars(N);
    cout<<"For N = "<<N<<endl;
    cout<<"Value of the crude MC is "<<get<0>(Var)<<endl;
    cout<<"Value of Conditioning MC is "<<get<1>(Var)<<endl;
    cout<<"Value of Anthithetic MC is " <<get<2>(Var)<<endl;
    cout<<"Value of Importance sampling MC is " <<get<3>(Var)<<endl;
    cout<<"Value of Importance sampling on Conditioning MC is " <<get<4>(Var)<<endl;
    cout<<endl;
    cout<<"Variance of the crude MC is "<<get<5>(Var)<<endl;
    cout<<"Variance of Conditioning MC is "<<get<6>(Var)<<endl;
    cout<<"Variance of Anthithetic MC is " <<get<7>(Var)<<endl;
    cout<<"Variance of Importance sampling MC is " <<get<8>(Var)<<endl;
    cout<<"Variance of Importance sampling on conditioning MC is " <<get<9>(Var)<<endl;
    cout<<endl;
}
