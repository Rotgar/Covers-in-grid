#include "cover.h"
using namespace std;

int **T1, **T2; // 2d arrays used to create bipartite graph. T1 holds numbers:
                // 0 - o, 1 - * which belongs to first side of bipartite graph
                // 2 - * which belongs to second side, 3 - * without neighbors, Cover is incremented and * removed
int Cover, V, Max; // Cover - result, Max - result of matching() makeGraph, V - vertices

void fillArrays()
{
  T1 = new int*[N], T2 = new int*[N];
  for(int i=0; i<N; ++i)
  {
    T1[i] = new int[M];
		T2[i] = new int[M];
  }
  for(int i=0; i<N; ++i)
	{
		for(int j=0; j<M; ++j)
		{
			T1[i][j] = (i + j) % 2 == 0 ? 1 : 2;
			T2[i][j] = 0;
		}
	}
}

Graph* makeGraph(string** T)
{
	int v1, v2; // vertice numbers on left and right side of bipartite graph
  v1 = v2 = Cover = 0;
  for(int i=0; i<N; ++i)
	{
		for(int j=0; j<M; ++j)
		{
      if(T[i][j] == "o")
      {
        T1[i][j] = 0;
      }
      else
      {
        if((i==0 || i!=0 && T[i-1][j] == "o") && (i==N-1 || i!=N-1 && T[i+1][j] == "o")
          && (j==0 || j!=0 && T[i][j-1] == "o") && (j==M-1 || j!=N-1 && T[i][j+1] == "o"))
        {
          T1[i][j] = 3; // has no neighbours
          Cover++;
        }

        else if(T1[i][j] == 1) // to 1st group of graph
        {
          v1++;
          T2[i][j] = v1;
        }
        else if(T1[i][j] == 2) // to 2nd group of graph
        {
          v2++;
          T2[i][j] = v2;
        }
      }
		}
	}

  // Create the graph
  Graph *g;
  g = new Graph(v1, v2);
	V = v1 + v2;
  // Make edges between vertices
  if(V > 1)
  {
    for(int i=0; i<N; ++i)
  	{
  		for(int j=0; j<M; ++j)
  		{
  			if(T1[i][j] == 1)
  			{
  				if(i!=0 && T1[i-1][j] == 2)
  				{ g->addEdge(T2[i][j], T2[i-1][j]); }
  				if(i!=N-1 && T1[i+1][j] == 2)
  				{	g->addEdge(T2[i][j], T2[i+1][j]); }
  				if(j!=0 && T1[i][j-1] == 2)
  				{	g->addEdge(T2[i][j], T2[i][j-1]); }
  				if(j!=M-1 && T1[i][j+1] == 2)
  				{	g->addEdge(T2[i][j], T2[i][j+1]); }
  			}
  		}
  	}
  }
  clear<int>(T2);
  clear<int>(T1);
  return g;
}

// Run Hopcroft-Karp algorithm
int algorithm(Graph *g)
{
  Max = g->matching();
  Cover+=V-Max;
  return Cover;
}
