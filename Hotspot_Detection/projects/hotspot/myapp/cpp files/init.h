
class coord{
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

class countgridcell{
    public:
    vector<coord> points;
    int countGrid;
    countGrid_Cell(){countGrid=0;}
};
