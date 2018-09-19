/*
Name: Harman Dhillon
Date: 9/19/18
Assignment: HW1
*/

// path finder - finds a path through a digital map read from a text file using a graph representation and breadth-first search
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "glut.h"	// GLUT Library (for graphics and user interaction)
#include "graph.h" // graph class

// Global constants 
const int LAND = 0;
const int WATER = 1;
const int MAXSIZE = 50;

// Global variables
int NUMROWS;
int NUMCOLS;
int cellsCount;  // total number of cells (rows*cols)
graph mapGraph; //graph object
int mapArray[MAXSIZE][MAXSIZE];// allows access all the info required to find connections between cells

// forward declaration - function called by graphics code included below
void findAndPrintPath();

#include "graphics.h" // application-specific graphics functions, uses global vars defined above

void createGraphFromMapFile() // reads the map file and initializes all global variables      
{

	//getting user input
	string fileName;
	cout << "Enter File Name" << endl;
	cin >> fileName;

	ifstream fileStream;
	fileStream.open(fileName);//opening file inorder to read through it

	fileStream >> NUMROWS;
	fileStream >> NUMCOLS;
	cellsCount = NUMROWS * NUMCOLS;

	if (fileStream.is_open()) {//if its open the loop through and pull data into a 2d array
		for (int r = 0; r < NUMROWS; ++r)
			for (int c = 0; c < NUMCOLS; ++c)
			{
				fileStream >> mapArray[r][c];
				mapGraph.addVertex();//placing a vertex in every cell
			}
	}
	fileStream.close();//closing file

	//Looping though the 2d array, and placing edges. 
	//Nice equation used to find the location in the array --> (r*NUMCOLS) + c --> [c+1 == right, c-1 == left, r-1 == up, r+1 == down]
	for (int r = 0; r < NUMROWS; ++r)
	{
		for (int c = 0; c < NUMCOLS; ++c)
		{
			if (mapArray[r][c] == LAND)//checking to see if current location is LAND
			{
				if (c + 1 < NUMCOLS && mapArray[r][c + 1] != WATER) //checking right for bounds and water
					mapGraph.addEdge((r*NUMCOLS) + c, ((r)* NUMCOLS + (c+1)));//placing edge
				if (c - 1 >= 0 && mapArray[r][c - 1] != WATER)//checking left for bounds and water
					mapGraph.addEdge((r*NUMCOLS) + c, ((r)* NUMCOLS + (c-1)));//placing edge
				if (r - 1 >= 0 && mapArray[r - 1][c] != WATER)//checking up for bounds and water
					mapGraph.addEdge((r*NUMCOLS) + c, ((r-1)* NUMCOLS + c));//placing edge
				if (r + 1 < NUMROWS && mapArray[r + 1][c] != WATER)//checking down for bounds and water
					mapGraph.addEdge((r*NUMCOLS) + c, ((r + 1)* NUMCOLS + c));//placing edge
				//Check up and then left and right, for diagonal paths
				if (r - 1 >= 0)
				{
					if (c - 1 >= 0 && mapArray[r - 1][c - 1] != WATER)//checking left for bounds and water
						mapGraph.addEdge((r*NUMCOLS) + c, ((r - 1)* NUMCOLS + (c-1)));//placing edge
					if (c + 1 < NUMCOLS && mapArray[r - 1][c + 1] != WATER)//checking right for bounds and water
						mapGraph.addEdge((r*NUMCOLS) + c, ((r - 1)* NUMCOLS + (c + 1)));//right
				}

				//Check down and then left and right, for diagonal paths
				if (r + 1 < NUMROWS)
				{
					if (c - 1 >= 0 && mapArray[r + 1][c - 1] != WATER)//checking left for bounds and water
						mapGraph.addEdge((r*NUMCOLS) + c, ((r + 1)* NUMCOLS + (c - 1)));//placing edge
					if (c + 1 < NUMCOLS && mapArray[r + 1][c + 1] != WATER)//checking right for bounds and water
						mapGraph.addEdge((r*NUMCOLS) + c, ((r + 1)* NUMCOLS + (c + 1)));//placing edge
				}

			}
		}
	}
}

void findAndPrintPath()
{
	mapGraph.breadthFirst(0);
	mapGraph.printPath(cellsCount-1);
}

int main(int argc, char** argv)
{
	createGraphFromMapFile();
	startGraphicsLoop(argc, argv);
	return 0;
}



