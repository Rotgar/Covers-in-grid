/* Mateusz Krawczyk AAL.12 - Stacje BTS */
#include <bits/stdc++.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <cctype>
#include <math.h>

#include "graph.h"
#include "generator.h"
#include "cover.h"
#include "timer.h"

using namespace std;

int N, M;// N - rows, M - column,  E - edges
Timer timer;    // Timer
Graph *g; // Pointer to graph

// T() complexity
double funcT(int n, int m)
{
  return n*m;
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
    int Cover = algorithm(g);
    cout<<"Cover: "<<Cover<<endl;
    delete g;
    clear<string>(T);
  }

  if(m == "-m2")
  {
    string _n, _m, _cov;
    _n = argv[2];
    if(_n!="-n") { cout<<"Wrong flag, should be -n"<<endl; exit(0); }
    _m = argv[4];
    if(_m!="-m") { cout<<"Wrong flag, should be -m"<<endl; exit(0); }
    _cov = argv[6];
    if(_cov!="-c") { cout<<"Wrong flag, should be -c"<<endl; exit(0); }

    N = stoi(argv[3]), M = stoi(argv[5]);
    int cov = stoi(argv[7]);

    T = generate(N, M, cov, 2);
    show<string>(T);
    fillArrays();
  	Graph* g = makeGraph(T);
    int Cover = algorithm(g);
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

    cout<<"Creating table..."<<endl<<endl;
    for(int i=0; i<k; ++i)
    {
      avgTime = 0;
      for(int j=0; j<r; ++j)
      {
        N = nxx, M = mxx;
        T = generate(N, M, cov, 2);

        timer.start();
        fillArrays();
        g = makeGraph(T);
        int Cover = algorithm(g);

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
