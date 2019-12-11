#define PI 3.14159
#define earthRadiusKm 6371.0

double deg2rad(double deg) {
  return (deg * PI / 180);
}
double rad2deg(double rad) {
  return (rad * 180 / PI);
}
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  double delta_phi=deg2rad(lat2d-lat1d);
  double delta_lambda=deg2rad(lon2d-lon1d);
  double a=pow(sin(delta_phi/2.0),2)+cos(lat1r)*cos(lat2r)*pow(sin(delta_lambda/2.0),2);
  double c=2*atan2(sqrt(a),sqrt(1-a));
  double m=earthRadiusKm*1000*c;

  return m/1000.0;
}
double distance(double lat1d,double lat2d,double lon1d=0,double lon2d=0) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  double delta_phi=deg2rad(lat2d-lat1d);
  double delta_lambda=deg2rad(lon2d-lon1d);
  double a=pow(sin(delta_phi/2.0),2)+cos(lat1r)*cos(lat2r)*pow(sin(delta_lambda/2.0),2);
  double c=2*atan2(sqrt(a),sqrt(1-a));
  double m=earthRadiusKm*1000*c;
  return m/1000.0;
}

void find_bottom_left(vector<coord> &pos,double &pxmin,double &pymin){
    for(int i=0;i<pos.size();i++){
        pxmin=min(pos[i].x,pxmin);
        pymin=min(pos[i].y,pymin);
    }
}
pair<double,double> sf,firstscale;
int nsdt=0;

void remove_negetive(vector<coord> &pos){
    double pxmin=inf,pymin=inf;
    find_bottom_left(pos,pxmin,pymin);
    sf = { pxmin,pymin };
    for(int i=0;i<pos.size();i++){
        pos[i].x-=sf.first;
        pos[i].y-=sf.second;
    }
    if(nsdt==0){firstscale=sf;}
    nsdt++;
}

void scaleback(double &xx, double &yy){
    xx+=sf.first;
    yy+=sf.second;
}

int getplanearea(vector<coord> &pos){
  double xmax = INT_MIN;
  double xmin = INT_MAX;
  double ymax = INT_MIN;
  double ymin = INT_MAX;
  for(int i=0;i<pos.size();i++){
      xmax= max(xmax, pos[i].x);
      ymax= max(ymax, pos[i].y);
      xmin= min(xmin, pos[i].x);
      ymin= min(ymin, pos[i].y);
    }
  int length=distance(xmin,xmax);
  int breadth=distance(ymin,ymax);
  int ed=max(length,breadth);
  areaS=ed*ed;
  sidelength=ed;
  return max(ceil(xmax-xmin),ceil(ymax-ymin));
}
