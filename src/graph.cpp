/* Mateusz Krawczyk AAL.12 - Stacje BTS */
#include "graph.h"
using namespace std;

int Graph::matching()
{
	// left[u] stores pair of u in matching where u
	// is a vertex on left side of Bipartite Graph.
	// If u doesn't have any pair, then left[u] is NIL
	left = new int[m+1];
	// right[v] stores pair of v in matching. If v
	// doesn't have any pair, then left[v] is NIL
	right = new int[n+1];
	// dist[u] stores distance of left side vertices
	// dist[u] is one more than dist[u'] if u is next
	// to u'in augmenting path
	dist = new int[m+1];

	// Initialize NIL as pair of all vertices
	for (int u=0; u<m+1; u++)
		left[u] = NIL;
	for (int v=0; v<n+1; v++)
		right[v] = NIL;

	int result = 0;

	// Keep updating the result while there is an augmenting path.
	while (bfs())
	{
		// Find a free vertex
		for (int u=1; u<=m; u++)
		{
			// If current vertex is free and there is an augmenting path from current vertex
			if (left[u]==NIL && dfs(u))
			{
				result++;
			}
		}
	}
	delete []left, right, dist;
	return result;
}
// Returns true if there is an augmenting path, else returns false
bool Graph::bfs()
{
	queue<int> Q; //an integer queue
	// First layer of vertices (set distance as 0)
	for (int u=1; u<=m; u++)
	{
		// If this is a free vertex, add it to queue
		if (left[u]==NIL)
		{
			// u is not matched
			dist[u] = 0;
			Q.push(u);
		}
		// Else set distance as infinite so that this vertex is considered next time
		else
		 dist[u] = INF;
	}

	// Initialize distance to NIL as infinite
	dist[NIL] = INF;
	// Q is going to contain vertices of left side only.
	int z = 0;
	while (!Q.empty())
	{
		// Dequeue a vertex
		int u = Q.front();
		Q.pop();

		// If this node is not NIL and can provide a shorter path to NIL
		if (dist[u] < dist[NIL])
		{
			// Get all adjacent vertices of the dequeued vertex u
			list<int>::iterator i;
			for (i=adj[u].begin(); i!=adj[u].end(); ++i)
			{
				int v = *i;
				// If pair of v is not considered so far (v, right[V]) is not yet explored edge.
				if (dist[right[v]] == INF)
				{
					// Consider the pair and add it to queue
					dist[right[v]] = dist[u] + 1;
					Q.push(right[v]);
				}
			}
		}
	}
	// If we could come back to NIL using alternating path of distinct
	// vertices then there is an augmenting path
	return
		(dist[NIL] != INF);
}

// Returns true if there is an augmenting path beginning with free vertex u
bool Graph::dfs(int u)
{
	if (u != NIL)
	{
		list<int>::iterator i;
		for (i=adj[u].begin(); i!=adj[u].end(); ++i)
		{
			// Adjacent to u
			int v = *i;
			// Follow the distances set by BFS
			if (dist[right[v]] == dist[u]+1)
			{
				if (dfs(right[v]) == true)
				{
					right[v] = u;
					left[u] = v;
					return true;
				}
			}
		}
		dist[u] = INF;
		return false;
	}
	return true;
}
// Constructor
Graph::Graph(int m, int n)
{
	this->m = m;
	this->n = n;
	adj = new list<int>[m+1];
}
// To add edge from u to v and v to u
void Graph::addEdge(int u, int v)
{
	adj[u].push_back(v); // Add u to v’s list.
}

// Show graph
void Graph::showGraph()
{
	list<int>::iterator iter;
	for(int i=0; i<m+1; ++i)
	{
		for (iter=adj[i].begin(); iter!=adj[i].end(); ++iter)
		{
				std::cout<<*iter<<" ";
		}
		std::cout<<std::endl;
	}
}
