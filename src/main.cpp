#include "graph.h"
#include<bits/stdc++.h>
using namespace std;



int N, M, Cover;
void show_i(int n, int** tab)
{
  for(int i=0; i<n; ++i)
  {
    for(int j=0; j<M; ++j)
    {
        cout<<tab[i][j]<<" ";
    }
    cout<<endl;
  }
  cout<<endl;
}

void show_s(int n, string** tab)
{
  for(int i=0; i<n; ++i)
  {
    for(int j=0; j<M; ++j)
    {
        cout<<tab[i][j]<<" ";
    }
    cout<<endl;
  }
  cout<<endl;
}

void findRows(string** T,int &v1, int &v2)
{
	v1 = v2 = 0;

	int **T1 = new int*[N], **T2 = new int*[N];
  for(int i=0; i<N; ++i)
  {
    T1[i] = new int[M];
		T2[i] = new int[M];
  }
	for(int i=0; i<N; ++i)
	{
		for(int j=0; j<M; ++j)
		{
			T1[i][j] = 0;
			T2[i][j] = 0;
		}
	}

	for(int i=0; i<N; ++i)
	{
		for(int j=0; j<M; ++j)
		{
			if(T[i][j] == "*")
			{
				if(T1[i][j] == 0)
				{
					T1[i][j] = 1;
					v1++;
					T2[i][j] = v1;
				}

				int neighbor = 0;
				if(j!=M-1 && T[i][j+1] == "*")
				{
					if(T1[i][j+1] == 0)
					{
						if(T1[i][j] == 1)
						{
							T1[i][j+1] = 2;
							v2++;
							T2[i][j+1] = v2;
						}
						if(T1[i][j] == 2)
						{
							T1[i][j+1] = 1;
							v1++;
							T2[i][j+1] = v1;
						}
					}
					neighbor++;
				}
				if(i!=N-1 && T[i+1][j] == "*")
				{
					if(T1[i][j] == 1)
					{
						T1[i+1][j] = 2;
						v2++;
						T2[i+1][j] = v2;
					}
					else
					{
						T1[i+1][j] = 1;
						v1++;
						T2[i+1][j] = v1;
					}
					neighbor++;
				}
				if(neighbor==0)
				{
					if(i==0 || i!=0 && T[i-1][j]!="*")
						neighbor++;
					if(j==0 || j!=0 && T[i][j-1]!="*")
						neighbor++;
					if(neighbor == 2)
					{
						T1[i][j] = 3;
						T2[i][j] = 0;
						v1--;
						Cover++;
					}
				}
			}
		}
	}
	show_i(N, T1);
	show_i(N, T2);
	cout<<"v1: "<<v1<<"v2: "<<v2<<endl;

	Graph g(v1, v2);

	for(int i=0; i<N; ++i)
	{
		for(int j=0; j<M; ++j)
		{
			if(T1[i][j] == 1)
			{
				if(i!=0 && T1[i-1][j] == 2)
					g.addEdge(T2[i][j], T2[i-1][j]);
				if(i!=N-1 && T1[i+1][j] == 2)
					g.addEdge(T2[i][j], T2[i+1][j]);
				if(j!=0 && T1[i][j-1] == 2)
					g.addEdge(T2[i][j], T2[i][j-1]);
				if(j!=M-1 && T1[i][j+1] == 2)
					g.addEdge(T2[i][j], T2[i][j+1]);
			}
		}
	}
	int V = v1 + v2, Max;
	Max = g.matching();
	Cover+= V-Max;
}

int main(int argc, char ** argv){

  if(argc < 2){
    cout<<"Too little arguments!"<<endl;
    exit(0);
  }
  N = stoi(argv[1]), M = stoi(argv[2]);
  //k=stoi(argv[3]);
  string **T = new string*[N];
  for(int i=0; i<N; ++i)
  {
    T[i] = new string[M];
  }

  fstream plik;
  plik.open("dane.txt");

  int i, j;
  for( i = 0; i < N; ++i)
  {
    for( j = 0; j < M; ++j)
    {
      plik>>T[i][j];
    }
  }
  plik.close();
  show_s(N, T);
	Cover = 0;
	int v1, v2;
	findRows(T, v1, v2);

	cout<<"Cover: "<<Cover<<endl;

	return 0;
}
