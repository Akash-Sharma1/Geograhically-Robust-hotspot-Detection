class dataset{
    public:
    vector<coord> pointSet;
    vector<coord> activitySet;
    public:
    long double pxmax,pxmin,pymax,pymin;

void find_bottom_left(vector<coord> &pos){
    pxmin=inf,pymin=inf;
    for(long i=0;i<pos.size();i++){
        pxmin=min(pos[i].x,pxmin);
        pymin=min(pos[i].y,pymin);
    }
}
pair<double,double> sf;//minimum subtractor
void remove_negative(vector<coord> &pos){
    find_bottom_left(pos);
    sf = { pxmin,pymin };
    pxmin=inf,pymin=inf,pxmax=0,pymax=0;
    for(long i=0;i<pos.size();i++){
        pos[i].x-=sf.first;
        pos[i].y-=sf.second;
        pxmin=min(pos[i].x,pxmin);
        pymin=min(pos[i].y,pymin);
        pxmax=max(pos[i].x,pxmax);
        pymax=max(pos[i].y,pymax);
    }
}
long double scale;
void variate(vector<coord>&pos){
    long double factorX,factorY;
    int n= pos.size();
    long double xmax = INT_MIN;
    long double xmin = INT_MAX;
    long double ymax = INT_MIN;
    long double ymin = INT_MAX;
    
    for(int i=0;i<n;i++){
      xmax= max(xmax, pos[i].x);
      ymax= max(ymax, pos[i].y);
      xmin= min(xmin, pos[i].x);
      ymin= min(ymin, pos[i].y);
    }
    //cout << xmax << " " << xmin << " " << ymin << " " << ymax << endl;
    factorX= 20/(xmax-xmin);
    factorY= 20/(ymax-ymin);
    //if(factorX <100) factorX= 100/factorX;
    //if(factorY < 100) factorY=100/factorY;
    cout << factorX << "      " << factorY << endl;
    scale=min(factorX,factorY);
    for(int i=0;i<n;i++){
      pos[i].x*=scale;
      pos[i].y*=scale;
    }
    for(int i=0;i<n;i++){
      xmax= max(xmax, pos[i].x);
      ymax= max(ymax, pos[i].y);
      xmin= min(xmin, pos[i].x);
      ymin= min(ymin, pos[i].y);
    }
    //cout << xmax << " " << xmin << " " << ymin << " " << ymax << endl;  
}

void scaleback(long double &xx, long double &yy, long double &rr){
    xx/=scale;
    yy/=scale;
    xx+=sf.first;
    yy+=sf.second;
    rr/=scale;
  }
    
    int readdataset(){
        freopen("demofile.txt","r",stdin);
        freopen("outputgen.txt","w",stdout);
        int n;
        cin>>n;
        string x,y;
        pointSet.resize(n);
        activitySet.resize(n);
        
        for(int i=0;i<n;i++){
          cin>>x>>y;
          pointSet[i].x=stod(x);
          pointSet[i].y=stod(y);
          activitySet[i]=pointSet[i];
        }
        variate(pointset);
        return activitySet.size();
    }
};
