class dataset{
    public:
    vector<coord> pointSet;
    vector<coord> activitySet;
    public:
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
        return activitySet.size();
    }
};
