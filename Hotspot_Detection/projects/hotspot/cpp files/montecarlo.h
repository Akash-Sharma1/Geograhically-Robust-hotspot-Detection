
double  rand_double () {
   return rand()/(double )RAND_MAX;
}
void generatemontecarlo(int m,double  montecarlo[])
{
    int i,j;
    for(i=0;i<m;i++)
    {
        vector<coord> crd;
        for(j=0;j<100;j++)
        {
            double  lat=fmod(rand(),N*lcell);
            if(lat<0)lat=-lat;
            double  lon=fmod(rand(),100);
            if(lon<0)lat=-lon;
            crd.push_back({lat,lon});
        }
        modP=crd.size();
        remove_negetive(crd);
        double differ=getplanearea(crd);
        lcell=differ/20.0;
        N=ceil(differ/lcell);
        rearth=2*distance(0,lcell);

        vector<pair<pair<int,int>,vector<coord> > > fset= Filter_Phase(crd);
        vector<pair<Circle,double > > Ctemp=Refine_Phase(fset);

        double  maxll=-inf;
        for(j=0;j<Ctemp.size();j++){
            if(Ctemp[i].second>maxll)
                maxll=Ctemp[i].second;
        }
        montecarlo[i]=maxll;
    }
}

//
//    srand(time(NULL));
//    double  montecarlo[msim];
//    memset(montecarlo,0,sizeof(montecarlo));
//
//    //generatemontecarlo(msim,montecarlo);
//    sort(montecarlo,montecarlo+msim,greater<double >());
//
//    vector<Circle> hotspotCircles;
//
//    for(int i=0;i<candidate_circles.size();i++){
//        for(int j=0;j<msim;j++){
//            if(candidate_circles[i].second>montecarlo[j]){
//                double  pval=((double )j)/((double )msim+1);
//                if(pval<=alphaP){
//                    hotspotCircles.push_back(candidate_circles[i].first);
//                }
//                break;
//            }
//        }
//    }
//
//    cout<<hotspotCircles.size()<<endl;
//    for(int i=0;i<hotspotCircles.size();i++){
//         scaleback(hotspotCircles[i].x,hotspotCircles[i].y,hotspotCircles[i].radius);
//         cout << hotspotCircles[i].x<<" " <<hotspotCircles[i].y<<" " <<hotspotCircles[i].radius << endl;}
