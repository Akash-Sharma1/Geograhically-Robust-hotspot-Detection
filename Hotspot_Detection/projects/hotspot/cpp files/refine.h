

bool is_pointliesincell(pair<int,int> c,double  x,double  y){
    double Xmin=grid[c.first][c.second].Xmin-5;
    double Xmax=grid[c.first][c.second].Xmax+5;
    double Ymin=grid[c.first][c.second].Ymin-5;
    double Ymax=grid[c.first][c.second].Ymax+5;
    if(x>=Xmin && x<=Xmax){
        if(y>=Ymin && y<=Ymax)return true;
    }
    return false;
}

#include "SEC.h"

vector<pair<Circle,double > > Refine_Phase(vector<pair<pair<int,int>,vector<coord> > > fset){

  vector<pair<Circle,double > > candidate_circles;
  for(int i=0;i<fset.size();i++){
    pair<int,int> cellcenter=fset[i].first;
    double r=inf;
    Circle maxC;
    double  maxllr=-1;

    while(fset[i].second.size()!=0 && r>=rearth){

      Circle C=makeSmallestEnclosingCircle(fset[i].second);
      r=C.r;
      C.noofpoints=fset[i].second.size();

      double  dis=-1;int mpos=-1;
      for(int j=0;j<fset[i].second.size();j++){
        double dd=distanceEarth(C.c.x,C.c.y,fset[i].second[j].x,fset[i].second[j].y);
        if(dis<dd){
          dis=dd;
          mpos=j;
        }
      }
      C.r=r=dis;
//cout<<r<<endl;
      //if(is_pointliesincell(cellcenter,C.c.x,C.c.y) && r>=rearth){
        double  llr=C.logLikelihood_circle();
        if(maxllr<llr && llr>thetha){
          maxllr=llr;
          maxC=C;
        }
     // }
      if(mpos!=-1)
        fset[i].second.erase(fset[i].second.begin()+mpos);
    }

    if(maxllr!=-1){
      candidate_circles.push_back({maxC,maxllr});
    }
  }
  cout<<"refine done : "<<candidate_circles.size()<<endl;
  return candidate_circles;
}
