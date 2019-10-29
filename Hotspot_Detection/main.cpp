#include <bits/stdc++.h>
using namespace std;
double power(double x, unsigned int y){double res = 1;while (y > 0){ if (y & 1){res = res*x;} y = y>>1;x = x*x;}return res;}
const int inf=1e9;
#define PI 3.14159
/*
latitute horizontal
longitute vertical
*/
struct coord{
    double lat,longi;
    coord(double a,double b){
        this->lat=a;
        this->longi=b;
    }
};
class coord_array{
public:
    vector<coord> pos;
    int sz;
    cood_array(){
        sz=0;
    }
    // finds most negetive coordinate
    int find_bottom_left(){
        double minl=inf;
        for(int i=0;i<sz;i++){
            if(minl>min(pos[i].lat,pos[i].longi) ){
                minl=min(pos[i].lat,pos[i].longi);
            }
        }
        return minl;
    }
    //this makes all coordinates postitive, starts them from 0, all points lie on the 1st quadrant
    void remove_negetive(){
        int neg=find_bottom_left();
        for(int i=0;i<sz;i++){
            pos[i].lat-=neg;
            pos[i].longi-=neg;
        }
    }
};


int modP,areaS,sidelength;

//  class for circles
class circles{
public:
    coord center;
    double radius,observed_points,expected_points,llr,areaofcircle;
    circles(coord c,int r,int np){
        center.longi=c.longi;
        center.lat=c.lat;
        radius=r;
        observed_points=np;
        areaofcircle=PI*r*r;
        expected_points=modP*areaofcircle/areaS;
    }
    //Interest measure of a circle
    void  log_likelihood_ratio(){
        llr=getllr();
    }
    double getllr(){
        if(!(observed_points>expected_points))return 0;
        double a=observed_points/expected_points;
        a=power(a,observed_points);
        double b=modP-observed_points;
        b/=(modp-expected_points);
        b=power(b,(modp-observed_points) );
        return a*b;
    }

}
class countGrid_Cell{
public:
    doubel Xmin,Xmax,Ymin,Ymax;
    int cell_count;
    countGrid_Cell(double Xmin,double Xmax,double Ymin,double Xmax,int cellcount){
      this->Xmin=Xmin;
      this->Xmax=Xmax;
      this->Ymin=Ymin;
      this->Ymax=Ymax;
      this->cell_count=cellcount;
    }
};
class Cubic_Grid:public countGrid_Cell
int main()
{
    //INPUTS
    int thetha,rmin,alphaP,mSim_m;
    thetha=0;
    rimn=2;
    alphaP=0.1;
    msim_m=5;

    // DATA SET OF TAXI

    //EXTRACT ONLY LOCATIONS

    // FINDING AREA OF SPACE AND NUMBER OF POINTS ON PLANE
    areaS=get_area_of_plane(points);
    modP=points.sz;

    //EXTRA VARIABLES
    int lcell=rmin/2;
    int N=sidelength/lcell;
    int total_countGrid_cells=N*N;

    return 0;
}
