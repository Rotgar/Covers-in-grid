/* Mateusz Krawczyk AAL.12 - Stacje BTS */
#include "graph.h"
#include "generator.h"
#include "Timer.h"

#include <bits/stdc++.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <cctype>
#include <math.h>
using namespace std;

int N, M, Cover=0, V, E, Max; // N - rows, M - column, Cover - result, Max - result of matching() makeGraph,
                              // V - vertices, E - edges
int **T1, **T2; // 2d arrays used to create bipartite graph. T1 holds numbers
                // 0 - o, 1 - *  that belongs to first side of bipartite graph
                // 2 - * that belongs to second side, 3 - * without neighbors, Cover is incremented and * removed
Timer timer;    // Timer
Graph *g;       // Pointer to graph
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

// T() complexity
double funcT(int n, int m)
{
    return n*m;
}

/* Fill array used for creating bipartite graph
T1 filled like 1 2 1 2
               2 1 2 1
               1 2 1 2
T2 filled with 0's
*/
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

// Create bipartite graph
Graph* makeGraph(string** T)
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
  E = 0;
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
  				{ g->addEdge(T2[i][j], T2[i-1][j]); E++; }
  				if(i!=N-1 && T1[i+1][j] == 2)
  				{	g->addEdge(T2[i][j], T2[i+1][j]); E++; }
  				if(j!=0 && T1[i][j-1] == 2)
  				{	g->addEdge(T2[i][j], T2[i][j-1]); E++; }
  				if(j!=M-1 && T1[i][j+1] == 2)
  				{	g->addEdge(T2[i][j], T2[i][j+1]); E++; }
  			}
  		}
  	}
  }
  clear<int>(T2);
  clear<int>(T1);
  return g;
}

// Run Hopcroft-Karp algorithm
void algorithm(Graph *g)
{
  Max = g->matching();
  Cover+=V-Max;
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
    { for( j = 0; j < M; ++j) { cin>>T[i][j]; } }

    fillArrays();
  	g = makeGraph(T);
    algorithm(g);
    cout<<"Cover: "<<Cover<<endl;
    delete g;
    clear<string>(T);
  }

  if(m == "-m2")
  {
    string _n, _m, _k;
    _n = argv[2];
    if(_n!="-n") { cout<<"Wrong flag, should be -n"<<endl; exit(0); }
    _m = argv[4];
    if(_m!="-m") { cout<<"Wrong flag, should be -m"<<endl; exit(0); }
    _k = argv[6];
    if(_k!="-k") { cout<<"Wrong flag, should be -k"<<endl; exit(0); }

    N = stoi(argv[3]), M = stoi(argv[5]);
    int k = stoi(argv[7]);

    T = generate(N, M, k, 2);
    show<string>(T);
    fillArrays();
  	Graph* g = makeGraph(T);
    algorithm(g);
    cout<<"Cover: "<<Cover<<endl;
    clear<string>(T);
    delete g;
  }

  if(m == "-m3")
  {
    string _nx, _mx, _cov, _k, _step, _r;
    _nx = argv[2];
    if(_nx!="-n") { cout<<"Wrong flag, should be -n"<<endl; exit(0); }
    int nx = stoi(argv[3]);
    _mx = argv[4];
    if(_mx!="-m") { cout<<"Wrong flag, should be -m"<<endl; exit(0); }
    int mx = stoi(argv[5]);
    _cov = argv[6];
    if(_cov!="-c") { cout<<"Wrong flag, should be -c"<<endl; exit(0); }
    int cov = stoi(argv[7]);
    _k = argv[8];
    if(_k!="-k") { cout<<"Wrong flag, should be -k"<<endl; exit(0); }
    int k = stoi(argv[9]);
    _step = argv[10];
    if(_step!="-step") { cout<<"Wrong flag, should be -step"<<endl; exit(0); }
    int step = stoi(argv[11]);
    _r = argv[12];
    if(_r!="-r") { cout<<"Wrong flag, should be -r"<<endl; exit(0); }
    int r = stoi(argv[13]);

    int mediana;
    mediana = k/2;

    double *Table = new double[k];
    double avgTime;
    int nxx = nx, mxx = mx;
    for(int i=0; i<k; ++i)
    {
      avgTime = 0;
      for(int j=0; j<r; ++j)
      {
        Cover = 0;
        N = nxx, M = mxx;
        T = generate(N, M, cov, 2);

        timer.start();
        fillArrays();
        g = makeGraph(T);
        algorithm(g);

        const auto elapsed = timer.time_elapsed();
        double t = (double)(elapsed.count()/1000000.0f);
        avgTime+=t;
        delete g;
        clear<string>(T);
      }
      avgTime = (double)(avgTime/r);
      Table[i] = avgTime;
      nxx+=step;
      mxx+=step;
    }

    double q, c = funcT(nx + mediana * step, mx + mediana * step)/Table[mediana];
    cout<<"n      m      t(n,m)[ms]     q(n,m)"<<endl;
    for(int i=0; i<k; ++i)
    {
      int n = nx + i * step;
      int m = mx + i * step;
      q = Table[i]/funcT(n, m) * c;
      cout<<n<<"     "<<m<<"     "<<Table[i]<<"      "<<q<<endl;
    }
    delete[] Table;
  }

	return 0;
}
