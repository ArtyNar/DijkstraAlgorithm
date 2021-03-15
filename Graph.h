#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <stack>
using namespace std;

template <typename Type>
class Graph;

template <typename Type>
ostream& operator << (ostream& out, const Graph<Type>& g);

template <typename Type>
class Graph {
private:
	vector<Type> verticies;
	vector<vector<Type>> edges;
	vector<vector<int>> distances; //Vector of distances
	vector<int> sums;              //Vector of sums of distances
	vector<int> path;              //Vector of sums of distances
	vector<vector<Type>> solved;
	int totalBest = 100000;

	int vertArr[20][20]; //the adjacency matrix
	int count = 0;
public:
	Graph();
	int getBest(){return totalBest;}
	void addVertex(Type vertex);
	void addEdge(Type, Type, int);
	int getVertexPos(Type item);
	int getNumVertices()const;
	bool isEdge(Type, Type);
	friend ostream& operator << <>(ostream& out, const Graph<Type>& g);
	vector<Type>getPath(Type, Type);
	bool pathHelper(Type, Type, vector<Type>&, vector<Type>&, int);
	bool isVisited(Type, vector<Type>);
};


/*********************************************
* Constructs an empty graph
*
*********************************************/
template<typename Type>
Graph<Type>::Graph() {

}

/*********************************************
* Adds a Vertex to the Graphs. Note that the vertex may not be an int value
*********************************************/
template <typename Type>
void Graph<Type>::addVertex(Type vertex)
{
	verticies.push_back(vertex);
	vector<Type>lst;
	edges.push_back(lst);
	distances.push_back(lst);
	sums.push_back(0);
}

/*********************************************
* Returns the current number of vertices
*********************************************/
template<typename Type>
int Graph<Type>::getNumVertices()const {
	return verticies.size();
}

/*********************************************
* Returns the position in the verticies list where the given vertex is located, -1 if not found.
*********************************************/
template <typename Type>
int Graph<Type>::getVertexPos(Type item)
{
	for (unsigned int i = 0; i < verticies.size(); i++)
	{
		if (item == verticies[i])
		{
			return i;
		}
	}
	return -1; //return negative one
}

/*********************************************
* Adds an edge going in the direction of source going to target
*********************************************/
template <typename Type>
void Graph<Type>::addEdge(Type source, Type target, int dist)
{
	int srcPos = getVertexPos(source);
	if (srcPos < 0)
	{
		throw runtime_error("Vertex not found");
	}
	vertArr[source][target] = dist;
	vertArr[target][source] = dist;
	edges[srcPos].push_back(target);
	distances[srcPos].push_back(dist);
}

template <typename Type>
bool Graph<Type>::isEdge(Type source, Type dest)
{
	int srcPos = getVertexPos(source);
	if (srcPos < 0)
	{
		throw runtime_error("Vertex not found");
	}
	for (unsigned int i = 0; i < edges[i].size(); i++)
	{
		if (edges[srcPos][i] == dest)
		{
			return true;
		}
	}
	return false;
}

/*********************************************
* Returns a display of the graph in the format
* vertex: edge edge
* Note: This is not a traversal, just output
*********************************************/
template <typename Type>
ostream& operator << (ostream& out, const Graph<Type>& g)
{
	for (unsigned int i = 0; i < g.verticies.size(); i++)
	{
		for (unsigned int e = 0; e < g.edges[i].size(); e++)
		{
			out << "[" << g.verticies[i] << "]--" << g.distances[i][e] << "--["<< g.edges[i][e] << "]; ";
		}
		out << endl;
	}
	out << endl;
	out << " |";
	for (int i = 0; i < g.verticies.size(); i++)
	{
		out << g.verticies[i] << " ";
	}
	out << endl << "-|-------------------" << endl;
	for (int i = 0; i < g.verticies.size(); i++)
	{
		out << g.verticies[i] << "|";
		for (int j = 0; j < g.verticies.size(); j++)
		{
			out << g.vertArr[i][j] << " ";
		}
		out << endl;
	}
	return out;
}

//function that returns the shortest path between any two points
template <typename Type>
vector<Type> Graph<Type>::getPath(Type source, Type dest) 
{
	vector<Type> solution;
	vector<Type> visited;
	pathHelper(source, dest, visited, solution, 0);
	return solution;
}

//helping recursive function for getPath
template <typename Type>
bool  Graph<Type>::pathHelper(Type source, Type dest, vector<Type>& visited, vector<Type>& solution, int best)
{	
	if (source == dest)
	{
		visited.push_back(source);
		//By removing this comment, you can see every step the program is taking recursively to calculate the path
		/*for (int i = 0; i < visited.size(); i++)
		{
			cout << visited[i] << " ";
		}
		cout << endl;
		cout << "Path length:  " << best << ". " << endl << endl;*/
		if (best < totalBest)
		{
			totalBest = best; 
			solution = visited; 
		}
		return true;
	}
	if (!isVisited(source, visited))
	{
		path.push_back(source);
		visited.push_back(source);
		vector<int> dists;
		int vertPos = getVertexPos(source);
		for (unsigned int e = 0; e < edges[vertPos].size(); e++)
		{
			dists.push_back(distances[vertPos][e]);
		}
		for (unsigned int e = 0; e < edges[vertPos].size(); e++)
		{
			while (visited[visited.size()-1] != source)
			{
				visited.pop_back();
			}
			pathHelper(edges[vertPos][e], dest, visited, solution, best + dists[e]);
		}
	}
}

template <typename Type>
bool Graph<Type>::isVisited(Type source, vector<Type> visited)
{
	for (int i = 0; i < visited.size(); i++)
	{
		if (visited[i] == source)
		{
			return true;
		}
	}
	return false;
}

