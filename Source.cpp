#include <iostream>
#include <string>
#include "Graph.h"
#include <vector>

using namespace std;
int main() {
	Graph<int>g;
	int verts[] = { 9, 2, 1, 7, 5, 4, 8, 3, 6, 0 };
	for (int i = 0; i < 10; i++) 
	{
		g.addVertex(verts[i]);
	}
	g.addEdge(0, 1, 2);
	g.addEdge(0, 2, 1);
	g.addEdge(0, 3, 5);
	g.addEdge(1, 4, 2);
	g.addEdge(4, 5, 3);
	g.addEdge(5, 6, 7);
	g.addEdge(3, 6, 4);
	g.addEdge(6, 7, 2);
	g.addEdge(2, 7, 3);
	g.addEdge(6, 8, 5);
	g.addEdge(5, 8, 4);
	g.addEdge(5, 9, 2);
	g.addEdge(9, 8, 1);

	g.addEdge(1, 0, 2);
	g.addEdge(2, 0, 1);
	g.addEdge(3, 0, 5);
	g.addEdge(4, 1, 2);
	g.addEdge(5, 4, 3);
	g.addEdge(6, 5, 7);
	g.addEdge(6, 3, 4);
	g.addEdge(7, 6, 2);
	g.addEdge(7, 2, 3);
	g.addEdge(8, 6, 5);
	g.addEdge(8, 5, 4);
	g.addEdge(9, 5, 2);
	g.addEdge(8, 9, 1);
	cout << "-----Welcome to my implementation of the Dijkstra's algorithm!-----" << endl << endl;
	cout << g << endl;
	while (true)
	{
		cout << "  [0]-----1-----[2]" << endl
			<< "  |  \\            \\" << endl
			<< "  2   5            3" << endl
			<< "  |    \\            \\" << endl
			<< "  [1]   [3]-4-[6]-2-[7]" << endl
			<< "  |          /  \\" << endl
			<< "  |         7    5" << endl
			<< "  |        /      \\" << endl
			<< "  2     [5]----4---[8]" << endl
			<< "  |    /   \\       /" << endl
			<< "  |   3     2     1" << endl
			<< "  |  /       \\   /" << endl
			<< "  [4]         [9]" << endl;

		cout << "-------------------------------------------------" << endl;

		cout << "Enter the nodes: ";
		int choice1;
		int choice2;
		cin >> choice1;
		cin >> choice2;
		vector<int>sol = g.getPath(choice1, choice2);
		cout << "Solution: ";
		for (int i = 0; i < sol.size(); i++)
		{
			cout << " " << sol[i];
		}
		cout << endl;
		cout << "Path Length: " << g.getBest();
		cout << endl << endl;
	}	
}


