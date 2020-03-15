#include <string>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// template <size_t rows, size_t cols>

bool checkAround(int (&elevation)[4][4], int posx, int posy, int dir){
	switch (dir)
	{
	    case 1:
	        //Check east
	        if((elevation[posx][posy] > elevation[posx][posy+1]) && (posy != 3)){
	        	return true;
			}
			else{
				return false;
			}
	        break;	
	    case 2:
	        //Check north
	        if((elevation[posx][posy] > elevation[posx-1][posy]) && (posx != 0)){
	        	return true;
			}
			else{
				return false;
			}
	        break;	        
		case 3:
	        //Check west
	        if((elevation[posx][posy] > elevation[posx][posy-1]) && (posy != 0)){
	        	return true;
			}
			else{
				return false;
			}
	        break;
		case 4:
			//Check south
			if((elevation[posx][posy] > elevation[posx+1][posy]) && (posx != 3)){
				return true;
			}
			else{
				return false;
			}			
			break;
	    default:
	    	cout << "ERROR: Incorrect direction";
			return false;
	    	break;
	}
}    

void loopAround(vector<int>* path, int* maxPathLength,vector<int>* longestPath, int (&elevation)[4][4], int posx, int posy)
{
	if(checkAround(elevation, posx, posy, 1)){
		cout << elevation[posx][posy+1];
		(*path).push_back(elevation[posx][posy+1]);
		if(((*path).size()>*maxPathLength) || (((*path).size()==*maxPathLength) && (((*longestPath).front()-(*longestPath).back())<((*path).front()-(*path).back())))){
			*maxPathLength = (*path).size();
			*longestPath = *path;
		}
		loopAround(path, maxPathLength, longestPath, elevation, posx, posy+1);			
	}
	if(checkAround(elevation, posx, posy, 2)){
		cout << elevation[posx-1][posy];
		(*path).push_back(elevation[posx-1][posy]);
		if(((*path).size()>*maxPathLength) || (((*path).size()==*maxPathLength) && (((*longestPath).front()-(*longestPath).back())<((*path).front()-(*path).back())))){
			*maxPathLength = (*path).size();
			*longestPath = *path;
		}
		loopAround(path, maxPathLength, longestPath, elevation, posx-1, posy);			
	}
	if(checkAround(elevation, posx, posy, 3)){
		cout << elevation[posx][posy-1];
		(*path).push_back(elevation[posx][posy-1]);
		if(((*path).size()>*maxPathLength) || (((*path).size()==*maxPathLength) && (((*longestPath).front()-(*longestPath).back())<((*path).front()-(*path).back())))){
			*maxPathLength = (*path).size();
			*longestPath = *path;
		}
		loopAround(path, maxPathLength, longestPath, elevation, posx, posy-1);			
	}
	if(checkAround(elevation, posx, posy, 4)){
		cout << elevation[posx+1][posy];
		(*path).push_back(elevation[posx+1][posy]);
		if(((*path).size()>*maxPathLength) || (((*path).size()==*maxPathLength) && (((*longestPath).front()-(*longestPath).back())<((*path).front()-(*path).back())))){
			*maxPathLength = (*path).size();
			*longestPath = *path;
		}
		loopAround(path, maxPathLength, longestPath, elevation, posx+1, posy);			
	}
	
	(*path).pop_back();	
}

int main () {
	int rows = 4;
	int cols = 4;
	int elevation[4][4] = {{4, 8, 7, 3}, {2, 5, 9, 3}, {6, 3, 2, 5}, {4, 4, 1, 6}};
	vector<int> path;
	vector<int> longestPath;
	int maxPathLength = 0;	

	int maxVal = 0;
	int posx;
	int posy;
	for(int i = 0; i < rows; i++){
		for(int j=0; j < cols; j++){
	 		if(elevation[i][j] > maxVal){
				maxVal = elevation[i][j];
				posx = i;
				posy = j;	
			}
		}	
	}
	
	path.push_back(elevation[posx][posy]);
	if((path.size()>maxPathLength) || ((path.size()==maxPathLength) && ((longestPath.front()-longestPath.back())<(path.front()-path.back())))){
		maxPathLength = path.size();
		longestPath = path;
	}
	
	if(checkAround(elevation, posx, posy, 1)){
		cout << elevation[posx][posy+1];
		path.push_back(elevation[posx][posy+1]);
		if((path.size()>maxPathLength) || ((path.size()==maxPathLength) && ((longestPath.front()-longestPath.back())<(path.front()-path.back())))){
			maxPathLength = path.size();
			longestPath = path;
		}
		loopAround(&path, &maxPathLength, &longestPath, elevation, posx, posy+1);		
	}			
	if(checkAround(elevation, posx, posy, 2)){
		cout << elevation[posx-1][posy];
		path.push_back(elevation[posx-1][posy]);
		if((path.size()>maxPathLength) || ((path.size()==maxPathLength) && ((longestPath.front()-longestPath.back())<(path.front()-path.back())))){
			maxPathLength = path.size();
			longestPath = path;
		}
		loopAround(&path, &maxPathLength, &longestPath, elevation, posx-1, posy);			
	}
	if(checkAround(elevation, posx, posy, 3)){
		cout << elevation[posx][posy-1];
		path.push_back(elevation[posx][posy-1]);
		if((path.size()>maxPathLength) || ((path.size()==maxPathLength) && ((longestPath.front()-longestPath.back())<(path.front()-path.back())))){
			maxPathLength = path.size();
			longestPath = path;
		}
		loopAround(&path, &maxPathLength, &longestPath, elevation, posx, posy-1);			
	}
	if(checkAround(elevation, posx, posy, 4)){
		cout << elevation[posx+1][posy];
		path.push_back(elevation[posx+1][posy]);
		if((path.size()>maxPathLength) || ((path.size()==maxPathLength) && ((longestPath.front()-longestPath.back())<(path.front()-path.back())))){
			maxPathLength = path.size();
			longestPath = path;
		}
		loopAround(&path, &maxPathLength, &longestPath, elevation, posx+1, posy);			
	}
	
	cout << "Now comes the longest path";
	for (int i = 0; i < longestPath.size(); i++) {		
		cout << longestPath.at(i) << ' ';
	}
	cout << endl;
	cout << maxVal << endl;
	cout << posx << endl;
	cout << posy << endl;
	
	
	return 0;
}
