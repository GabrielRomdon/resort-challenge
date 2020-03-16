#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

// Global variables for the size of the matrix
size_t rowN; // Number of rows
size_t colN; // Number of columns

bool checkAround(int** elevation, int posx, int posy, int dir){
	switch (dir)
	{
	    case 1:
	        //Check East
			if (posy == colN-1) // Detect possible overflow
				return false;
	        else if((elevation[posx][posy] > elevation[posx][posy+1]))
	        	return true;
			else
				return false;
	    case 2:
	        //Check North
			if(posx == 0) // Detect possible overflow
				return false;
	        else if(elevation[posx][posy] > elevation[posx-1][posy])
	        	return true;
			else
				return false;
		case 3:
	        //Check West
			if (posy == 0) // Detect possible overflow
				return false;
	        else if(elevation[posx][posy] > elevation[posx][posy-1])
	        	return true;
			else
				return false;
		case 4:
			//Check South
			if (posx == rowN-1) // Detect possible overflow
				return false;
			if(elevation[posx][posy] > elevation[posx+1][posy])
				return true;
			else
				return false;
	    default:
			// Invalid direction
	    	throw dir;
	}
}    


void loopAround(vector<int>* path, int* longestPathLength,vector<int>* longestPath, int** elevation, int posx, int posy, int** usedPath)
{
	// Check if the East value is lower
	if(checkAround(elevation, posx, posy, 1)){
		// If it is lower then append the value to the current path
		(*path).push_back(elevation[posx][posy+1]); 
		usedPath[posx][posy+1] += 1; // Update the usedPath array
		/* If the current path is longer than the longestPath and it is also steeper, then this is the longest path */
		if(((*path).size()>*longestPathLength) || (((*path).size()==*longestPathLength) && (((*longestPath).front()-(*longestPath).back())<((*path).front()-(*path).back())))){
			*longestPathLength = (*path).size();
			*longestPath = *path;
		}
		// Call function to loopAround again in the four directions
		loopAround(path, longestPathLength, longestPath, elevation, posx, posy+1, usedPath);			
	}
	// Check if the North value is lower
	if(checkAround(elevation, posx, posy, 2)){
		(*path).push_back(elevation[posx-1][posy]);
		usedPath[posx-1][posy] += 1;
		if(((*path).size()>*longestPathLength) || (((*path).size()==*longestPathLength) && (((*longestPath).front()-(*longestPath).back())<((*path).front()-(*path).back())))){
			*longestPathLength = (*path).size();
			*longestPath = *path;
		}
		loopAround(path, longestPathLength, longestPath, elevation, posx-1, posy, usedPath);			
	}
	// Check if the West value is lower
	if(checkAround(elevation, posx, posy, 3)){
		(*path).push_back(elevation[posx][posy-1]);
		usedPath[posx][posy-1] += 1;
		if(((*path).size()>*longestPathLength) || (((*path).size()==*longestPathLength) && (((*longestPath).front()-(*longestPath).back())<((*path).front()-(*path).back())))){
			*longestPathLength = (*path).size();
			*longestPath = *path;
		}
		loopAround(path, longestPathLength, longestPath, elevation, posx, posy-1, usedPath);			
	}
	// Check if the South value is lower
	if(checkAround(elevation, posx, posy, 4)){
		(*path).push_back(elevation[posx+1][posy]);
		usedPath[posx+1][posy] += 1;
		if(((*path).size()>*longestPathLength) || (((*path).size()==*longestPathLength) && (((*longestPath).front()-(*longestPath).back())<((*path).front()-(*path).back())))){
			*longestPathLength = (*path).size();
			*longestPath = *path;
		}
		loopAround(path, longestPathLength, longestPath, elevation, posx+1, posy, usedPath);			
	}
	
	// Once all the directions have been checked remove the last value
	(*path).pop_back();	
}


int main () {
	try{
		/* Obtain number of rows and columns from the first line*/
		ifstream file("map.txt");
		if(file.is_open())
		{
			file >> rowN;
			file >> colN;
		}

		/* Define the 'elevation' matrix that corresponds to the map elevation numbers*/
		int** elevation = new int*[rowN];
		for(size_t i = 0; i < rowN; ++i)
			elevation[i] = new int[colN];

		/* Fill the matrix with the values from the file */
		if(file.is_open())
		{
			for(int i = 0; i < rowN; i++)
			{
				for (int j = 0; j < colN; j++)
					file >> elevation[i][j];
			}
		}

		/* Define the 'usedPath' matrix that corresponds to the fields that have been used already */
		int** usedPath = new int*[rowN];
		for(size_t i = 0; i < rowN; ++i)
			usedPath[i] = new int[colN];

		/* Initialize the usedPath matrix as zeroes*/
		for(int i = 0; i < rowN; i++)
			{
				for (int j = 0; j < colN; j++){
					usedPath[i][j] = 0;
				}
			}
		
		vector<int> path; //Stores the current path
		vector<int> longestPath; //Stores the overall longest path
		int longestPathLength = 0;	//Stores the leght of the longest path
		int maxVal;
		int posx; // xPosition of the current cell in the matrix
		int posy; // yPosition of the current cell in the matrix
			
		do{
			path.clear();
			int maxVal = 0;
			/* Iteration for finding the highes values that haven't been used yet*/
			for(int i = 0; i < rowN; i++){
				for(int j=0; j < colN; j++){
					if(elevation[i][j] > maxVal && usedPath[i][j] == 0){
						maxVal = elevation[i][j];
						posx = i;
						posy = j;	
					}
				}	
			}
			cout << maxVal << endl;
			/* Leave the loop when the next 'maximum' value is lower than the longest path found */
			if (maxVal < longestPathLength){
				break;
			}

			/* Start a new path */
			path.push_back(elevation[posx][posy]);
			usedPath[posx][posy] += 1;

			/* If the current path is longer than the longestPath and it is also steeper, then this is the longest path */
			if((path.size()>longestPathLength) || ((path.size()==longestPathLength) && ((longestPath.front()-longestPath.back())<(path.front()-path.back())))){
				longestPathLength = path.size();
				longestPath = path;
			}
			
			loopAround(&path, &longestPathLength, &longestPath, elevation, posx, posy, usedPath);			
		}
		while(maxVal != 0);

		cout << "This is the longest path: ";
		for (int i = 0; i < longestPath.size(); i++)		
			cout << longestPath.at(i) << ' ';

		for(int i = 0; i < rowN; ++i)
			delete elevation[i];
		delete[] elevation;

		for(int i = 0; i < rowN; ++i)
			delete usedPath[i];
		delete[] usedPath;

	}
	catch (int dir) {
		cout << "Incorrect direction." << endl;
   	}
	return 0;
}
