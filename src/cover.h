/* Mateusz Krawczyk AAL.12 - Stacje BTS */
#ifndef COVER_H
#define COVER_H
#include <string>

#include "graph.h"

extern int N, M;
extern Graph *g;

// Create bipartite graph
Graph* makeGraph(string** T);

// Run Hopcroft-Karp algorithm
int algorithm(Graph *g);

/* Fill array used for creating bipartite graph
T1 filled like 1 2 1 2
               2 1 2 1
               1 2 1 2
T2 filled with 0's
*/
void fillArrays();

// Show 2d table of T-parameter, for example int or string
template<typename T>
void show(T** tab)
{
  for(int i=0; i<N; ++i)
  {
    for(int j=0; j<M; ++j)
    {
        cout<<tab[i][j]<<" ";
    }
    cout<<endl;
  }
  cout<<endl;
}

// Clear 2d table of T-parameter, for example int or string
template<typename T>
void clear(T** tab)
{
  for(int i=0; i<N; ++i)
  {
    delete [] tab[i];
  }
  delete[] tab;
}
#endif //COVER_H
