#include <bits/stdc++.h>
using namespace std;
const int inf=1e9;

double thetha,areaS,rearth,lcell;
int modP,sidelength,N;

struct coord{
    public: double  x,y;
    public:
        coord subtract(const coord &p) const;
        double distance(const coord &p) const;
	// Signed area / determinant thing
        double cross(const coord &p) const;
    coord(){
        this->x=0;
        this->y=0;
    }
    coord(double  a,double  b){
        this->x=a;
        this->y=b;
    }
};

struct countGrid_Cell{
    double  Xmin,Xmax,Ymin,Ymax;
    int cell_count;
    countGrid_Cell(){cell_count=0;}
};
countGrid_Cell grid[100][100];

#include "scaling.h"

double  log_LRGrid_Upperbound(int nMecc,int nMfcc,double  areaMecc,double  areaMfcc){
  int uc=nMecc;
  int lc=nMfcc;
  double  ub=areaMecc*modP/areaS;
  double  lb=areaMfcc*modP/areaS;

  if(!(uc>lb))return -inf;

  double  a=uc/lb;
  a=uc*log(a);
  double  b;
  if(lc>=ub){
    b=modP-lc;
    b/=(modP-ub);
    b=(modP-uc)*log(b);
  }
  else{
    b=0;
  }
  return a+b;
}

bool lieincircle(double  a,double  b,double r,double x,double y){
  double rd=distanceEarth(a,b,x,y);
  return rd<=r;
}

#include "filter.h"
#include "refine.h"
#include "montecarlo.h"

int main()
{

    freopen("randompoints.txt","r",stdin);
    //freopen("outputgen.txt","w",stdout);
    //freopen("C:\\Users\\aakas\\Documents\\Geograhically-Robust-hotspot-Detection\\Hotspot_Detection\\projects\\hotspot\\myapp\\static\\myapp\\outputgen.txt","w",stdout);
    int msim=10,n;
    thetha=10;
    double alphaP=0.001;

    cin>>n;
    vector<coord> points(500);
    for(int i=0;i<500;i++){
      string x;
      cin>>x;
      points[i].x=stod(x);
      cin>>x;
      points[i].y=stod(x);
    }
    modP=points.size();
    remove_negetive(points);

    double differ=getplanearea(points);
    lcell=differ/20;
    N=ceil(differ/lcell);
    rearth=distance(0,lcell);

    cout<<"area: "<<areaS<<"\nedge: "<<sidelength<<"\nN: "<<N<<"\ncell_length: "<<lcell<<"\nrearth: "<<rearth<<endl<<endl;

    vector<pair<pair<int,int>,vector<coord> > > fset= Filter_Phase(points);
    vector<pair<Circle,double > > candidate_circles=Refine_Phase(fset);

    cout<<candidate_circles.size()<<endl;
    for(int i=0;i<candidate_circles.size();i++){
         scaleback(candidate_circles[i].first.c.x,candidate_circles[i].first.c.y);
         cout << candidate_circles[i].first.c.x<<" " <<candidate_circles[i].first.c.y<<" " <<candidate_circles[i].first.r << endl;
    }
    return 0;
}
