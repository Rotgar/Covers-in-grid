/* Mateusz Krawczyk AAL.12 - Stacje BTS */
#ifndef GRAPH_H
#define GRAPH_H
#include<bits/stdc++.h>
#define NIL 0
#define INF INT_MAX

using namespace std;

class Graph
{
	// m and n are number of vertices on left and right sides of Bipartite Graph
	int m, n;

	// adj[u] stores adjacents of left side
	// vertex 'u'. The value of u ranges from 1 to m.
	// 0 is used for dummy vertex
	list<int> *adj;

	// Pointers to arrays needed for hopcroftKarp()
	int *left, *right, *dist;

public:
	Graph(int m, int n); // Constructor
	void addEdge(int u, int v); // To add edge

	// Returns true if there is an augmenting path
	bool bfs();

	// Adds augmenting path if there is one beginning with u
	bool dfs(int u);

	// Returns size of maximum matching
	int matching();

	// Shows graph
	void showGraph();
};
#endif //GRAPH_H
