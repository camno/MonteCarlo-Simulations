#include <iostream>
#include <fstream>
//#include <boost/tuple/tuple.hpp>
//#include "gnuplot-iostream/gnuplot-iostream.h"
#define a 6  // Fig.2.2, pg. 49 Monte Carlo Methods in Financial Engineering 2003
#define m 11 // 11
#define q 1  // q = [m/a]
#define r 5  // r =m mod a
using namespace std;

// linear congruential generator
int linear_rand(int seed=1 )
{
    static int x = seed; //integer variable holding the current x_i
    int k; 
    x = a*x % 11;  //since m is not too large.
    if (x<0) {
        x=x+m;
    }
    return x ;
}


int main(){
//    Gnuplot gp;
    double ui,uj; // random variables between 0-1
 //   vector<pair<double, double> > xy_pts; //gnuplot vector
    int seed; 
    ofstream myfile;
    seed = 1;
    myfile.open("points_b.csv");
    ui = ((double) linear_rand(seed))/(m);
    myfile<<ui<<"\n";
    for(int i=0;i<10;i++){ 
        uj = ((double) linear_rand(seed))/(m);
        myfile<<uj<<"\n";
        //xy_pts.push_back(make_pair(ui, uj)); // store ui,uj to vector
        ui = uj;                               //update ui
    }
    //gp <<"set xrange [0:1]\n set yrange [0:1]\n";
    //gp <<"plot"<<gp.file1d(xy_pts)<<"with points title 'circle'" <<endl;
    myfile.close();
    return 0;
}