pair<long,long> MFCC_MECC(double cx,double cy,double  radius,int var){
  int nmcc=0;
  int sz=0;
    for(int i=0;i<=N;i++){
        for(int j=0;j<=N;j++){
            coord *a=new coord(grid[i][j].Xmin,grid[i][j].Ymin);
            coord *b=new coord(grid[i][j].Xmin,grid[i][j].Ymax);
            coord *c=new coord(grid[i][j].Xmax,grid[i][j].Ymin);
            coord *d=new coord(grid[i][j].Xmax,grid[i][j].Ymax);
            if(var){
                if((lieincircle(cx,cy,radius,a->x,a->y) && lieincircle(cx,cy,radius,b->x,b->y) && lieincircle(cx,cy,radius,c->x,c->y) && lieincircle(cx,cy,radius,d->x,d->y))){
                    nmcc+=grid[i][j].cell_count;
                    sz++;
                }
            }
            else{
                 if((lieincircle(cx,cy,radius,a->x,a->y) || lieincircle(cx,cy,radius,b->x,b->y) || lieincircle(cx,cy,radius,c->x,c->y) || lieincircle(cx,cy,radius,d->x,d->y))){
                    nmcc+=grid[i][j].cell_count;
                    sz++;
                }
            }
        }
    }
  return {nmcc,sz};
}
vector<pair<pair<int,int>,vector<coord> > > Filter_Phase(vector<coord> &pos){
  double gridx=0;
  for (int i=0;i<=N;i++){
    double gridy=0;
    for(int j=0;j<=N;j++){
        grid[i][j].Xmin=gridx;
        grid[i][j].Xmax=gridx+lcell-.00000001;
        grid[i][j].Ymin=gridy;
        grid[i][j].Ymax=gridy+lcell-.00000001;
        gridy+=lcell;
        grid[i][j].cell_count=0;
    }
    gridx+=lcell;
  }
  for(int i=0;i<pos.size();i++){
    int x=floor(pos[i].x/lcell);
    int y=floor(pos[i].y/lcell);
    grid[x][y].cell_count++;
  }

  vector<pair<pair<int,int>,vector<coord> > > filtered_set;
  int deleted=0;
  double ed=((double)sidelength)/(double)N;
  ed*=ed;
  while(deleted!=pos.size()){
    double  LLR=-1,cr=0.0;
    int cx,cy;

    for(int i=0;i<=N;i++){
      for(int j=0;j<=N;j++){
        double  cenx=(grid[i][j].Xmin+grid[i][j].Xmax)/2;
        double  ceny=(grid[i][j].Ymin+grid[i][j].Ymax)/2;

        for(double r=rearth;r<sidelength/2;){

          pair<long,long> p1=MFCC_MECC(cenx,ceny,r,0);
          pair<long,long> p2=MFCC_MECC(cenx,ceny,r,1);

          double areaMecc=ed*p1.second;
          double areaMfcc=ed*p2.second;
          int nMecc=p1.first;
          int nMfcc=p2.first;

          if(areaMfcc==0){
            cout<<"0h";
          }
          double  llr=log_LRGrid_Upperbound(nMecc,nMfcc,areaMecc,areaMfcc);

          if(llr>=thetha && llr>LLR){
              LLR=llr;
              cx=i;cy=j;cr=r;
              //cout<<cenx<< " "<<ceny<<" "<<cr<<" "<<p1.first<<" "<<p2.first<<" "<<llr<<endl;
          }
            r+=rearth/2;
        }
      }
    }
    if(LLR>=thetha){
      int flag=0;
      double  cenx=(grid[cx][cy].Xmin+grid[cx][cy].Xmax)/2;
      double  ceny=(grid[cx][cy].Ymin+grid[cx][cy].Ymax)/2;
      vector<coord> v;
      for(int idx=0;idx<pos.size();idx++){
        if(pos[idx].x!=-inf){
            int i=floor(pos[idx].x/lcell);
            int j=floor(pos[idx].y/lcell);
            coord *a=new coord(grid[i][j].Xmin,grid[i][j].Ymin);
            coord *b=new coord(grid[i][j].Xmin,grid[i][j].Ymax);
            coord *c=new coord(grid[i][j].Xmax,grid[i][j].Ymin);
            coord *d=new coord(grid[i][j].Xmax,grid[i][j].Ymax);
             if((lieincircle(cenx,ceny,cr,a->x,a->y) || lieincircle(cenx,ceny,cr,b->x,b->y) || lieincircle(cenx,ceny,cr,c->x,c->y) || lieincircle(cenx,ceny,cr,d->x,d->y))){
                v.push_back(pos[idx]);
                pos[idx].x=pos[idx].y=-inf;
                grid[i][j].cell_count--;
                flag++;
            }
        }
      }
      deleted+=flag;
      cout<<"items: "<<flag<<endl;
//      if(!flag){
//        cout<<"filter Breakout : "<<filtered_set.size()<<endl;
//        break;
//      }
      filtered_set.push_back({{cenx,ceny},v});
    }
    else break;
  }
  cout<<"filter done : "<<filtered_set.size()<<endl;
  return filtered_set;
}
