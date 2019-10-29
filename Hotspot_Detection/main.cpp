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
void remove_negetive(vector<coord> &pos){
    int neg=find_bottom_left();
    for(int i=0;i<pos.size();i++){
        pos[i].x-=neg;
        pos[i].y-=neg;
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
////////////////////////////////////////////// MECC MFCC LLR /////////////////////////////////
vector<coord>  MECC(double x,double y, int radius,vector<coord> &p){
  // return points in mecc

}
vector<coord>  MFCC(double x,double y, int radius,vector<coord> &p){
  // return center gridcoord , radius and noof points in mecc circle

}
double log_LRGrid_Upperbound(double areaMecc,double areaMfcc,int nMecc,int nMfcc){
  int uc=nMecc;
  int lc=nMfcc;
  int ub=areaMecc*modP/areaS;
  int lb=areaMfcc*modP/areaS;

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
///////////////////////////////////////////////////////////////////////////////////////////
bool liesincircle(double a,double b,int r,coord p){
  // (x-a)2+(y-b)2=r2
  double rd=(p.x-a)*(p.x-a)+(p.y-b)*(p.y-b);
  return rd<=r;
}

countGrid_Cell grid[N][N];

vector<pair<pair<int,int>,vector<coord> > > Filter_Phase(vector<int> pos,int thetha){
  for(int i=0;i<pos.size();i++){
    int x=pos[i].x/lcell;
    int y=pos[i].y/lcell;
    if(grid[x][y].cell_count==0){
        grid[x][y].Xmin=grid[x][y].Ymin=-inf;
        grid[x][y].Xmax=grid[x][y].Ymax=inf;
    }
    grid[x][y].Xmin=min(grid[x][y].Xmin,x);
    grid[x][y].Xmax=min(grid[x][y].Xmax,x);
    grid[x][y].Ymin=min(grid[x][y].Ymin,y);
    grid[x][y].Ymax=min(grid[x][y].Ymax,y);
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
vector<vector<coord> > Refine_Phase(vector<pair<pair<int,int>,vector<coord> > > fset,int thetha){
  for(int i=0;i<fset.size();i++){

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
    vector<coord> points;
    remove_negetive(points);
    pair<int,int> p=getplanearea(points);
    areaS=p.first;//plane area
    sidelength=p.second;//plane side
    modP=points.sz;//no of points on plane

    //GRID VARIABLES
    int lcell=rmin/2;
    int N=sidelength/lcell;
    int total_countGrid_cells=N*N;
    total_cubicGrid_cells=N*N*N;

    //3 PHASES
    vector<pair<pair<int,int>,vector<coord> > > fset= Filter_Phase(points,thetha);
    Refine_Phase(fset,thetha);
    Monte_Carlo_Phase();

    return 0;
}
