#include <bits/stdc++.h>
using namespace std;
const long long inf=1e9;
const double PI= 3.1415926535897;

#include "init.h"
#include "dataset.h"

#include "SEC.h"



    countgridcell countGridCells[100][100];
    double circleGridB[100][100][100];
    double circleGridc[100][100][100];
    double circleGridULR[10000][8];
    int filledCircle[100][100];

class hotspot{

public:
    double theta = 100;
	int cellSize = 5;
	double xmax = 50;
	double ymax = 50;
	double xmin = 0;
	double ymin = 0;

	int ctot;
	int xCells;
    int yCells;
    int cellArea;
	double cellBaseline;
    int maxRadius;

    dataset Dataset;

public:
    bool compare(double a[], double b[]) {
					return a[7]>b[7];
				}

    double minCircle (vector<coord> &, bool , coord &, vector<coord> &);
    void enc3(coord A, coord B, coord C, coord &center);
    double computeTol (vector<coord> &points);


    double lrupper(int ctot, double uc, double ub, double lc, double lb);
    int unique(int ii);
    void writePointList (double circleGridULR_first[], vector<vector<coord>> &filterset, int size_x, int size_y, int counter);
    void setdiff (vector<vector<coord>> &filterset, int counter);
    double LikelihoodRatio(int ctot, double c, double B);
    int pdist2(vector<coord> &tmpSet, double appX, double appY);


    void runalgo(){

        ctot = Dataset.readdataset();

        for (int i = 0; i<ctot; i++){
            xmax=max(xmax,Dataset.pointSet[i].x);
            xmin=min(xmin,Dataset.pointSet[i].x);
            ymax=max(ymax,Dataset.pointSet[i].y);
            ymin=min(ymin,Dataset.pointSet[i].y);
        }

        double studyArea = (xmax - xmin) * (ymax - ymin);

		////cout<<"Activity Set |A| = " << ctot<<endl;
		////cout<<"Study Area S = " << studyArea<<endl;
        xCells = (int)ceil((xmax - xmin) / cellSize);
		yCells = (int)ceil((ymax - ymin) / cellSize);
        cellArea = cellSize * cellSize;
        ////cout<<"x: "<<xCells<<" y: "<<yCells<<" ctot: "<<ctot<<endl;

		cellBaseline = ((double)(ctot * cellArea)) / studyArea; // expected number of points in a cell

		if (xCells < yCells)
			maxRadius = xCells / 2;
		else
			maxRadius = yCells / 2;

        for (int i = 0; i<ctot; i++){
			int xCoord = abs((int)floor((Dataset.pointSet[i].x - xmin) / cellSize)); // which cell a point goes to
			int yCoord = abs((int)floor((Dataset.pointSet[i].y - ymin) / cellSize));

//			//cout<<"i: " << i<<" xCoord = "<<xCoord<<" yCoord = "<<yCoord<<endl;

			if (xCoord >= xCells)
				xCoord--;
			if (yCoord >= yCells)
				yCoord--;

			countGridCells[xCoord][yCoord].points.push_back(Dataset.pointSet[i]);
			countGridCells[xCoord][yCoord].countGrid++;
		}

		vector<vector<coord>> filterset;
		//countgridcell countGridCells[xCells][yCells];

		bool flag = true;
		int counter = 0;//filterset size

		vector<vector<double> > ulrList;

		while(flag==true){
//                double circleGridB[xCells][yCells][maxRadius];
//                double circleGridc[xCells][yCells][maxRadius];
//                double circleGridULR[xCells*yCells*maxRadius][8];
//                int filledCircle[xCells][yCells];

                memset(circleGridB,0,sizeof(circleGridB));
                memset(circleGridc,0,sizeof(circleGridc));
                memset(circleGridULR,0,sizeof(circleGridULR));
                memset(filledCircle,0,sizeof(filledCircle));// Mecc grid

                int ii=0;

                for (int x = 0; x < xCells; x++){
				for (int y = 0; y < yCells; y++){
					for (int radius = 1; radius <= maxRadius; radius++){
                        //for mecc and mfcc
						for (int k = 0; k < xCells; k++){
							for (int l = 0; l < yCells; l++){
							    if ( ((k - x)*(k - x) + (l - y)*(l - y)) < radius * radius ){
									filledCircle[k][l] = 1;
									circleGridB[x][y][radius-1]++;
									circleGridc[x][y][radius-1] += countGridCells[k][l].countGrid;
								}
							}
						}
                        if (radius >= 2){
							double lB = circleGridB[x][y][radius-2] * cellBaseline; // maximum bounded
							double lc = circleGridc[x][y][radius-2];
							double uB = circleGridB[x][y][radius-1] * cellBaseline; // minimal bounding
							double uc = circleGridc[x][y][radius-1];

							if (lc < uB){
								lc = uB;
							}
							if ((uB <= ctot) && (lB > 0) && (uc >= lB)){

								double lru = lrupper(ctot, uc, uB, lc, lB);//logirithmic upper bound
								if (lru >= theta){
									circleGridULR[ii][0] = x; // cell index of the center
									circleGridULR[ii][1] = y;
									circleGridULR[ii][2] = radius;
									circleGridULR[ii][3] = lc;
									circleGridULR[ii][4] = lB;
									circleGridULR[ii][5] = uc;
									circleGridULR[ii][6] = uB;
									circleGridULR[ii][7] = lru;
									ii++;
								}
							}
						}
					}
				}
			}
			//checking false ones
			for (int i = 0; i < ii; i++){
				if (circleGridULR[i][7] <= theta){
					////cout<<"fault\n";
					for (int j = 0; j < 8; j++){
						circleGridULR[i][j] = 0;
					}
				}
				////cout<<"filterset: "<<i<<" : "<<circleGridULR[i][0]<<" "<<circleGridULR[i][1]<<" "<<circleGridULR[i][2]<<" "<<circleGridULR[i][7]<<endl;
			}
			// equivalent to "sort rows with the 8th column"
			for (int i=0;i<ii;i++){
                if(circleGridULR[i][7]>circleGridULR[0][7]){
                    for(int j=0;j<8;j++){
                        swap(circleGridULR[0][j],circleGridULR[i][j]);
                    }
                }
			}
			//Removing Duplicates%%%%%%%%%%%%%%%%%%%
			int nRows=unique(ii);
			ii=nRows;

			if (nRows > 0){
                vector<coord> tmp;
				filterset.push_back(tmp);

				writePointList(circleGridULR[0], filterset, xCells, yCells, counter);

                vector<double> temp;
				for(int i=0;i<8;i++){temp.push_back(circleGridULR[0][i]);}
				ulrList.push_back(temp);

				setdiff(filterset, counter); // delete points that are in filterset[counter] from Pointset
			}
			if ( (Dataset.pointSet.size() <= 0) || ((circleGridULR[0][0] == 0)&&(circleGridULR[0][1] == 0)&&(circleGridULR[0][2] == 0)&&(circleGridULR[0][3] == 0)&&(circleGridULR[0][4] == 0)&&(circleGridULR[0][5] == 0)&&(circleGridULR[0][6] == 0)&&(circleGridULR[0][7] == 0)) ) {
				flag = false;
			}
			counter++; // each loop find one filter set, which is one potential circle
		}

		for(int i = filterset.size()-1; i >= 0; i--){
			if (filterset[i].size() == 0){
				filterset.erase(filterset.begin()+i);
				i--;
			}
		}
        // for debugging
	//	for (int i = 0; i < filterset.size(); i++){
			//cout<<"filterset " <<i<< " size: " << filterset[i].size()<<endl;
//			for (int j = 0; j < filterset[i].size(); j++){
//				//cout<<"("<<filterset[i][j].x<<", "<<filterset[i][j].y<<") "<<endl;
//			}
//			//cout<<endl;
		//}

		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		// ------------------------------- refine phase starts -----------------------

		//cout<<"Refine phase starts!"<<endl;

		//cout<<"filterset size: "<< filterset.size()<<endl;
		dataset p;
		if (filterset.size() > 0){

			double finalLR[filterset.size()][7];
			memset(finalLR,0,sizeof(finalLR));
			double radius = inf; // this "radius" different from the previous one?

			for (int i = 0; i < filterset.size(); i++){

				vector<coord> tmpSet; // clone filterset{i}
				vector<coord> circlePoints;

				tmpSet.clear();

				for (int j = 0; j < filterset[i].size(); j++){
					tmpSet.push_back(filterset[i][j]); // clone filterset element
				}

				double previousLR = 0; // used to get the max LR for a pruned set
				bool newflag = true;

				while (newflag == true){

					coord center;
					//radius = minCircle(tmpSet, true, center, circlePoints);//given minimum enclosing circle
                    Circle cc=makeSmallestEnclosingCircle(tmpSet);
                    radius=cc.r;
                    center=cc.c;

					double c = (double)tmpSet.size();
					double area = radius * radius * PI;
					double B = area * ctot / studyArea;
					double likelihoodRatio = LikelihoodRatio(ctot, c, B);

					if ( radius!=0 && (likelihoodRatio > previousLR) && (c >= 2) ){ // new max LR circle
						finalLR[i][0] = center.x;
						finalLR[i][1] = center.y;
						finalLR[i][2] = radius;
						finalLR[i][3] = area;
						finalLR[i][4] = B;
						finalLR[i][5] = c;
						finalLR[i][6] = likelihoodRatio;
						previousLR = likelihoodRatio;
					}
					if ( (tmpSet.size() > 0) && (circlePoints.size() > 0) ){
						double appX = xmin + ulrList[i][0] * cellSize - ((double)cellSize) / 2; // center of circle candidate
						double appY = ymin + ulrList[i][1] * cellSize - ((double)cellSize) / 2;
						int poi = pdist2(tmpSet, appX, appY);//index
						tmpSet.erase(tmpSet.begin()+poi);
					}
					else {
						newflag = false;
					}
				}
			}
			for (int i = 0; i < filterset.size(); i++){
				if(finalLR[i][6] > theta){
					p.variate(finalLR[i][0],finalLR[i][1],finalLR[i][2]);
					cout<<finalLR[i][0]<<" "<<finalLR[i][1]<<" "<<finalLR[i][2]<<endl;
							//<<" area: "<<finalLR[i][3]<< " nPoints: " << finalLR[i][5] <<" LR: "<<finalLR[i][6]<<endl;
				}
			}
		}

		//%%%%%%%%%%%%%FILTER AND REFINE DONE%%%%%%%%%%%
    }

};
#include "util.h"
//#include "quickhull.h"

int main()
{
    hotspot hset;
    hset.runalgo();
    return 0;
}
