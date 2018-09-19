/*
Name: Harman Dhillon
Date: 9/19/18
Assignment: HW1
*/

#include "graph.h"

// adds a vertex to the graph and assign it the next available id
void graph::addVertex()
{
	vertex unoVertex;
	unoVertex.path = NULL;//setting a default value

	//adding a unqie id based of the postion of unoVertex in the vertices vector
	if (vertices.size() != 0)
		unoVertex.id = vertices.size();
	else
		unoVertex.id = 0; //if it did not have a size, then the position is zero

	//adding the new vertex to the end list of vertices
	vertices.push_back(unoVertex);
}
// adds an undirected edge between vertices with the given ids
void graph::addEdge(int id1, int id2)
{
	//adding numbers to each other
	vertices[id1].neighbors.push_back(&vertices[id2]);
	vertices[id2].neighbors.push_back(&vertices[id1]);
}
 // conducts a breadth-first search from the vertex with the specified id
void graph::breadthFirst(int start)
{
	queue<vertex*> q;//stack of vertexs

	for (int i = 0; i < vertices.size(); ++i)
		vertices[i].distance = LONG_MAX;//setting each default size to a large number

	vertices[start].distance = start;//setting first distance to the start
	q.push(&vertices[start]);//pushing the start on the q

	//going through the q, conducting a breadth-first search
	while (!q.empty())
	{
		vertex* v = q.front();
		q.pop();
		list<vertex*>::iterator itr;
		for (itr = v->neighbors.begin(); itr != v->neighbors.end(); ++itr) {//getting all neighbors
			vertex* vTemp = *itr;
			if (vTemp->distance == LONG_MAX)//checking distance
			{
				vTemp->distance = v->distance + 1;
				vTemp->path = v;
				q.push(vTemp);
			}
		}
	}
}
// prints all the vertex ids along the path from the start vertex of the last search to this end vertex (includes end points)
void graph::printPath(int end)
{
	stack<int> sPaths; //stack of ids
	//adding the end on the stack
	int i = end;
	sPaths.push(i);
	//going through the vertices pulling ids from the previously connect vertex
	while (i != NULL)
	{
		if (vertices[i].path != nullptr)//bounds check for paths without solutions
		{
			i = vertices[i].path->id;//getting the last paths location
			sPaths.push(i);
		}
		
	}
	//poping the stack and displaying the location.
	while (!sPaths.empty())
	{
		cout << sPaths.top() << endl;
		sPaths.pop();
	}
}