/* Mateusz Krawczyk AAL.12 - Stacje BTS */
#include "graph.h"
#include "generator.h"
#include "Timer.h"

#include<bits/stdc++.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <cctype>
#include <math.h>
using namespace std;

int N, M, Cover=0, V, E, Max; // N - rows, M - column, Cover - result, Max - result of matching() algorithm,
                              // V - vertices, E - edges
int **T1, **T2; // 2d arrays used to create bipartite graph. T1 holds numbers
                // 0 - o, 1 - *  that belongs to first side of bipartite graph
                // 2 - * that belongs to second side, 3 - * without neighbors, Cover is incremented and * removed
Timer timer;

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

double maxO(double x, double y)
{
  if(x>y)
    return x;
  else
    return y;
}

// T() complexity
double funcT(int n)
{
  double d = pow(V, 2.5);
  double e = pow(V, 0.5) * E;
  //cout<<"d: "<<d<<endl;
  //cout<<"e: "<<e<<endl;
  return maxO(2*N*M, e);
}

// Fill array used for creating bipartite graph
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

// The algorithm. First the bipartite graph is created and then the algorithm used to count the cover
void algorithm(string** T)
{
	int v1, v2; // vertice numbers on left and right side of bipartite graph
  v1 = v2 = 0;
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
          T1[i][j] = 3;
          Cover++;
        }

        else if(T1[i][j] == 1)
        {
          v1++;
          T2[i][j] = v1;
        }
        else if(T1[i][j] == 2)
        {
          v2++;
          T2[i][j] = v2;
        }
      }
		}
	}
  //show<string>(T);
  //show<int>(T1);
  //show<int>(T2);

  // Create the graph
  Graph g(v1, v2);

  E = 0;

  // Make edges between vertices
	for(int i=0; i<N; ++i)
	{
		for(int j=0; j<M; ++j)
		{
			if(T1[i][j] == 1)
			{
				if(i!=0 && T1[i-1][j] == 2)
				{ g.addEdge(T2[i][j], T2[i-1][j]); E++; }
				if(i!=N-1 && T1[i+1][j] == 2)
				{	g.addEdge(T2[i][j], T2[i+1][j]); E++; }
				if(j!=0 && T1[i][j-1] == 2)
				{	g.addEdge(T2[i][j], T2[i][j-1]); E++; }
				if(j!=M-1 && T1[i][j+1] == 2)
				{	g.addEdge(T2[i][j], T2[i][j+1]); E++; }
			}
		}
	}
	V = v1 + v2, Max;

  cout<<"V: "<<V<<" E: "<<E<<endl;
  Max = g.matching();
  Cover+=V-Max;
  clear<int>(T2);
  clear<int>(T1);
}

int main(int argc, char ** argv){

  srand(time(NULL));
  string **T;

  if(argc < 2){
    cout<<"Too little arguments!"<<endl;
    exit(0);
  }

  string m = argv[1];
  if(m == "-m1")
  {

    cin>>N;
    if(cin.fail()){cout<<"Wrong N! Check input file."<<endl; exit(0);}
    cin>>M;
    if(cin.fail()){cout<<"Wrong M! Check input file."<<endl; exit(0);}

    T = new string*[N];
    for(int i=0; i<N; ++i)
    {
      T[i] = new string[M];
    }

    int i, j;
    for( i = 0; i < N; ++i)
    {
      for( j = 0; j < M; ++j)
      {
        cin>>T[i][j];
      }
    }
    fillArrays();
  	algorithm(T);
    cout<<"Cover: "<<Cover<<endl;
    clear<string>(T);
  }

  if(m == "-m2")
  {
    N = stoi(argv[2]), M = stoi(argv[3]);
    int k = stoi(argv[4]);

    T = generate(N, M, k, 2);
    show<string>(T);
    fillArrays();
  	algorithm(T);
    cout<<"Cover: "<<Cover<<endl;
    clear<string>(T);
  }

  if(m== "-m3")
  {
    //N = 1000, M = 1000;
    /*int enter = 1000, step = 500;
    int r = 5, k = 20;
    int mediana = k/2;
*/
    N = stoi(argv[2]);
    M = stoi(argv[3]);

    int enter = stoi(argv[4]);
    int k = stoi(argv[5]);
    int step = stoi(argv[6]);
    int r = stoi(argv[7]);

    int mediana;
    mediana = k/2;

    double *Table = new double[k];
    double avgTime;
    int l = enter;
    for(int i=0; i<k; ++i)
    {
      avgTime = 0;
      for(int j=0; j<r; ++j)
      {
        Cover = 0;
        T = generate(N, M, l, 2);
        fillArrays();
        timer.start();
      	algorithm(T);
        const auto elapsed = timer.time_elapsed();
        double t = (double)(elapsed.count()/1000000.0f);
        avgTime+=t;
      }
      avgTime = (double)(avgTime/r);
      Table[i] = avgTime;
      l+=step;
      clear<string>(T);
    }

    double q;
    double c = funcT(mediana)/Table[mediana];
    for(int i=0; i<k; ++i)
    {
      int n = enter + i * step;
      q = Table[i]/funcT(n) * c;
      cout<<n<<"  "<<Table[i]<<"  "<<q<<endl;
    }
    delete[] Table;
  }

	return 0;
}
