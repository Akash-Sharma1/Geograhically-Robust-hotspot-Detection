
    double hotspot::lrupper(int ctot, double uc, double ub, double lc, double lb){

		double logcin = log(uc);
		double logbin = log(lb);
		double logcout = log(ctot - lc);
		double logbout = log(ctot - ub);
		double lru;

		if( (uc > lb) && (lc >= ub) ) {
			lru = (uc * (logcin - logbin)) + ((ctot - uc) * (logcout - logbout));
		}
		else if ((uc > lb) && (lc < ub)){
			lru = (uc * (logcin - logbin)) + 1;
		}
		else{
			lru = 0;
		}
		return lru;
	}

	int hotspot::unique(int ii){

        map< pair<double,pair<double,double>>,int > dup;
        double temp[ii][8];
        int c=0;
        for(int i=0;i<ii;i++){
            if( dup[{circleGridULR[i][0],{circleGridULR[i][1],circleGridULR[i][2]}}] == 0 ){
                dup[{circleGridULR[i][0],{circleGridULR[i][1],circleGridULR[i][2]}}] = 1;
                for(int j=0;j<8;j++){
                    temp[c][j]=circleGridULR[i][j];
                }
                c++;
            }
        }
        for(int i=0;i<c;i++){
            for(int j=0;j<8;j++){
                circleGridULR[i][j]=temp[i][j];
            }
        }
        return c;
	}

	void hotspot::writePointList (double circleGridULR_first[], vector<vector<coord>> &filterset, int size_x, int size_y, int counter){

		double cenx=circleGridULR_first[0];
		double ceny=circleGridULR_first[1];
		double cenR=circleGridULR_first[2];

		for (int i = 0; i < size_x; i++){
			for (int j = 0; j < size_y; j++){

				if ( ((i-cenx)*(i-cenx)+(j-ceny)*(j-ceny))<(cenR*cenR) ){

					filledCircle[i][j] = 1; // cell [x, y] is in the circle

					for (int k = 0; k < countGridCells[i][j].points.size(); k++){
						filterset[counter].push_back(countGridCells[i][j].points[k]);
					}
					countGridCells[i][j].points.clear();
					countGridCells[i][j].countGrid = 0;
				}
				else{
					filledCircle[i][j] = 0; // cell [x, y] is not in the circle
				}
			}
		}
	}

	void hotspot::setdiff (vector<vector<coord>> &filterset, int counter){
		// same as "setdiff" in Matlab
		map<pair<double,double> ,int> mp;
		for (int i = filterset[counter].size()-1; i >= 0; i--){
            mp[{filterset[counter][i].x,filterset[counter][i].y}]=1;
			
		}
		int flag=0;
		while(!flag){
			flag=1;
			for(int i=0;i<Dataset.pointSet.size();i++){
				if( mp[ {Dataset.pointSet[i].x,Dataset.pointSet[i].y} ] == 1){
					flag=0;
					Dataset.pointSet.erase(Dataset.pointSet.begin()+i);
					i--;
				}
			}
		}
	}

	double hotspot::LikelihoodRatio(int ctot, double c, double B){
		double logc = log(c);
		double logb = log(B);
		double logctotc = log((double)ctot-c);
		double logctotb = log((double)ctot-B);
		double logLR;
		if (c > B){
			logLR = c * (logc - logb) + (double)(ctot - c) * (logctotc-logctotb);
		}
		else{
			logLR = 0;
		}
		return logLR;
	}

	int hotspot::pdist2(vector<coord> &tmpSet, double appX, double appY){
		// returns index of point in tmpSet farthest from the center
		int size = tmpSet.size();
		int poi = 0;
		double max_square = 0;
		double temp_square;

		for (int i = 0; i < size; i++){
			temp_square = (tmpSet[i].x - appX)*(tmpSet[i].x - appX) + (tmpSet[i].y - appY)*(tmpSet[i].y - appY);
			if (temp_square > max_square ){
				max_square = temp_square;
				poi = i;
			}
		}
		return poi;//index
	}
