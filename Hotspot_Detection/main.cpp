#include <bits/stdc++.h>
using namespace std;
double power(double x, unsigned int y){double res = 1;while (y > 0){ if (y & 1){res = res*x;} y = y>>1;x = x*x;}return res;}
const int inf=1e9;
#define PI 3.14159

//////////////////////////////////////// COORDINATES ///////////////////////
struct coord{
    double x,y;
    coord(double a,double b){
        this->x=a;
        this->y=b;
    }
};
int find_bottom_left(vector<coord> &pos){
    double minl=inf;
    for(int i=0;i<pos.size();i++){
        if(minl>min(pos[i].x,pos[i].y) ){
            minl=min(pos[i].x,pos[i].y);
        }
    }
    return minl;
}
double scalefactor;
void remove_negetive(vector<coord> &pos){
    scalefactor=find_bottom_left();
    for(int i=0;i<pos.size();i++){
        pos[i].x-=scalefactor;
        pos[i].y-=scalefactor;
    }
}

pair<int,int> getplanearea(vector<coord> &pos){
  int xmin,xmax,ymin,ymax;
  for(int i=0;i<pos.size();i++){
    xmin=min(xmin,pos[i].x);
    ymin=min(ymin,pos[i].y);
    xmax=min(xmax,pos[i].x);
    ymax=min(ymax,pos[i].y);
  }
  int edge=max(abs(xmax-xmin),abs(ymax,ymin));
  return {edge*edge,edge};
}

/////////////////////////////////////////////////////// COUNT GRID ////////////////////////////////////
int modP,areaS,sidelength;
int lcell,N,total_countGrid_cells,total_cubicGrid_cells;
// A SINGLE CELL CELLCOUNT NUMBER OF POINTS FROM XMIN TO XMAX, YMIN TO YMAX IN A SINGLE CELL
struct countGrid_Cell{
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
countGrid_Cell grid[N][N];
////////////////////////////////////////////// MECC MFCC LLR /////////////////////////////////

bool liesincircle(double a,double b,int r,coord p){
  // (x-a)2+(y-b)2=r2
  double rd=(p.x-a)*(p.x-a)+(p.y-b)*(p.y-b);
  return rd<=r;
}
vector<coord>  MECC(double x,double y, int radius,vector<coord> &p){
  vector<coord> meccpoints;
  for(int m=0;m<p.size();m++){
    int i=p[m].x/lcell;
    int j=p[m].y/lcell;

    coord a=new coord(grid[i][j].Xmin,grid[i][j].Ymin);
    coord b=new coord(grid[i][j].Xmin,grid[i][j].Ymax);
    coord c=new coord(grid[i][j].Xmax,grid[i][j].Ymin);
    coord d=new coord(grid[i][j].Xmax,grid[i][j].Ymax);

    if(lieincircle(x,y,radius,a) || lieincircle(x,y,radius,b) || lieincircle(x,y,radius,c) || lieincircle(x,y,radius,d)){
      meccpoints.push_back(p[m]);
    }
  }
  return meccpoints;
}

vector<coord>  MFCC(double x,double y, int radius,vector<coord> &p){
  vector<coord> mfccpoints;
  for(int m=0;m<p.size();m++){
    int i=p[m].x/lcell;
    int j=p[m].y/lcell;

    coord a=new coord(grid[i][j].Xmin,grid[i][j].Ymin);
    coord b=new coord(grid[i][j].Xmin,grid[i][j].Ymax);
    coord c=new coord(grid[i][j].Xmax,grid[i][j].Ymin);
    coord d=new coord(grid[i][j].Xmax,grid[i][j].Ymax);

    if(lieincircle(x,y,radius,a) && lieincircle(x,y,radius,b) && lieincircle(x,y,radius,c) && lieincircle(x,y,radius,d)){
      mfccpoints.push_back(p[m]);
    }
  }
  return mfccpoints;
}
double log_LRGrid_Upperbound(double areaMecc,double areaMfcc,int nMecc,int nMfcc){
  int uc=nMecc;
  int lc=nMfcc;
  double ub=areaMecc*modP/areaS;
  double lb=areaMfcc*modP/areaS;

  if(!(uc>lb))return log(0);

  double a=uc/lb;
  a=power(a,uc);
  double b;
  if(lc>=ub){
    b=modP-lc;
    b/=(modp-ub);
    b=power(b,(modp-uc) );
  }
  else{
    b=1;
  }
  return log(a*b);
}
class circle{
public:
  double x,y,radius;
  int noofpoints;
  double logLikelihood_circle(double areaS,int modP){
      double areaCircle=3.14*radius*radius;
      double B=(areaCircle/areaS)*modP;
      int C=noofpoints;
      if(!C>B)return log(0);
      double a=(C/B);
      a=power(a,C);
      double b=(modP-C)/(modP-B);
      b=power(b,(modP-C));
      return log(a*b*I);
  }
};
/////////////////////////////////////////////////////// PHASES //////////////////////////////////////////////////////////
vector<pair<pair<int,int>,vector<coord> > > Filter_Phase(vector<int> pos,int thetha){
  for(int i=0;i<pos.size();i++){
    int x=pos[i].x/lcell;
    int y=pos[i].y/lcell;
    if(grid[x][y].cell_count==0){
        grid[x][y].Xmin=x*lcell;
        grid[x][y].Ymin=y*lcell;
        grid[x][y].Xmax=x*lcell+lcell-0.00001;
        grid[x][y].Ymax=y*lcell+lcell-0.00001;
    }
    grid[x][y].cell_count++;
  }
  vector<pair<pair<int,int>,vector<coord> > > filtered_set;
  int sett=0;

  while(!pos.empty()){
    double maxxLLR=-1;
    int maxxX,maxxY,maxxR,xx,yy;

    for(int i=0;i<N;i++){
      for(int j=0;j<N;j++){
        for(int r=1;r<=N/2;r++){

          double cenx=(grid[i][j].Xmin+grid[i][j].Xmax)/2;
          double ceny=(grid[i][j].Ymin+grid[i][j].Ymax)/2;
          vector<coord> cirmecc=MECC(cenx,ceny,r,pos);
          int nMecc=cirmfcc.size();
          double areaMecc=PI*r*r;
          vector<coord> cirmfcc=MFCC(cenx,ceny,r,pos);
          int nMfcc=cirmfcc.size();
          double areaMfcc=PI*r*r;
          double llr=log_LRGrid_Upperbound(nMecc,nMfcc,areaMecc,areaMfcc);
          if(llr>=thetha && llr>maxLLR){
              maxLLr=llr;
              maxxX=cenx;maxxY=ceny;maxxR=r;xx=x;yy=y;
          }
        }
      }
    }
    if(maxxLLR!=-1){
      filtered_set.push_back({{xx,yy},{}});
      for(int i=0;i<pos.size();i++){
        if(liesincircle(maxxX,maxxY,maxxR,pos[i])){
          filtered_set[sett].push_back(pos[i]);
          pos.erase(pos.begin()+i);
          i--;
        }
      }
      ++set;
    }

  }
  return filtered_set;
}
// This is diffrent from mecc
circle find_smallest_enclosing_circle(){

}
vector<circles> Refine_Phase(vector<pair<pair<int,int>,vector<coord> > > fset,int thetha,int rmin){
  vector<circles> candidate_circles;
  for(int i=0;i<fset.size();i++){
    pair<int,int> cellcenter=fset[i].first;
    int r=inf;
    double cenx=(grid[i][j].Xmin+grid[i][j].Xmax)/2;
    double ceny=(grid[i][j].Ymin+grid[i][j].Ymax)/2;
    circle maxC;
    double maxllr=-1;
    
    while(fset[i].second.size()!=0 && r>=rmin){
      circle C=new circle;
      C=find_smallest_enclosing_circle();
      if(lieincell(cellcenter,C.x,C.y) && C.radius>=rmin){
        r=C.radius;
        double llr=C.logLikelihood_circle();//parameters yet to be defined
        if(maxllr<llr){
          maxllr=llr;
          maxC=C;
        }
      }
      // farthest from center of cellcount
      double dis=-1;int mpos;
      for(int j=0;j<fset[i].second.size();j++){
        if(dis>abs(fset[i].second[j].x-cenx)+abs(fset[i].second[j].y-ceny)){
          dis=abs(fset[i].second[j].x-cenx)+abs(fset[i].second[j].y-ceny);
          mpos=j;
        }
      }
      fset[i].second.erase(fset[i].second.begin()+mpos);
    }
    if(maxllr!=-1){
      candidate_circles.push_back(maxC);
    }
  }
  return candidate_circles;
}

double rand_double() {
   return rand()/(double)RAND_MAX;
}
int getPoissonRandom(int u)
{
  double L=exp((-1)*u);
  double p = 1.0;
  int k = 0;

  do {
    //cout<<"1"<<endl;
    k++;
    p *= rand_double();
  } while (p > L);

  return k - 1;
}

void generatemontecarlo(int m,double montecarlo[5000],double areaS)
{
    double rmin=0.5;
    int u=10;
    int i,j;

    for(i=0;i<m;i++)
    {
        vector< pair<double,double > > cord;
        cout<<"New dataset"<<endl;
        for(j=0;j<60;j++)
        {
            double lat=fmod(rand(),ldiff);
            double lon=fmod(rand(),bdiff);
            cord.push_back({lat,lon});
            cout<<lat<<" "<<lon<<endl;
        }
        vector< Circle > circle=getCircles(cord,rmin);
        double maxll=-999;
        for(j=0;j<circle.size();j++)
        {
            double ll=logLikelihood(cord,circle[j],areaS);

            if(ll>maxll)
                maxll=ll;
        }
        //cout<<maxll<<endl;
        montecarlo[i]=maxll;

    }
}

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
    vector<coord> points;//dataset
    remove_negetive(points);
    pair<int,int> p=getplanearea(points);
    areaS=p.first;//plane area
    sidelength=p.second;//plane side
    modP=points.sz;//no of points on plane

    //GRID VARIABLES
    double lcell=rmin/2;
    int N=sidelength/lcell;
    int total_countGrid_cells=N*N;
    total_cubicGrid_cells=N*N*N;

    //3 PHASES
    vector<pair<pair<int,int>,vector<coord> > > fset= Filter_Phase(points,thetha);
    vector<circles> candidate_circles=Refine_Phase(fset,thetha,rmin);
    Monte_Carlo_Phase();

    return 0;
}
