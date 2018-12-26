#include "generator.h"

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>

std::string **generate(int n, int m, int k, int l)
{
	int max;
	bool np, mp;
	np = mp = false;
	if (n % 2 == 1 && m % 2 == 1)
	{
		max = (n*(m - 1) + n - 1) / 2;
	}
	else
	{
		max = n * m / 2;
		if (n % 2 == 0)
		{
			np = true;
		}
		if (m % 2 == 0)
		{
			mp = true;
		}
	}

	if (k > max)
	{
		std::cout << "k too big!" << std::endl;
		exit(0);
	}
	else if (k == 0)
	{
		std::cout << "k equal 0!" << std::endl;
		exit(0);
	}

	std::string **T = new std::string*[n];
	int **Covered = new int*[n];
	for (int i = 0; i < n; ++i)
	{
		T[i] = new std::string[m];
		Covered[i] = new int[m];
	}
	int *Stars = new int[2 * k];
	int stars = 0, cover = k;
	bool more;
	std::string s;

	if (k < max / 2 + 2)
	{
		more = false;
		s = "o";
	}
	else
	{
		more = true;
		s = "*";
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			T[i][j] = s;
			Covered[i][j] = 0;
		}
	}

	if (!more)
	{
		while (k > 0)
		{
			int	y = rand() % n, x = rand() % m;
			if (Covered[y][x] == 0)
			{
				T[y][x] = "*";
				Covered[y][x] = 1;
				Stars[stars] = y, Stars[stars + 1] = x;
				stars += 2;

				if (y != 0)
				{
					Covered[y - 1][x] = 2;
				}
				if (y != n - 1)
				{
					Covered[y + 1][x] = 2;
				}
				if (x != 0)
				{
					Covered[y][x - 1] = 2;
				}
				if (x != m - 1)
				{
					Covered[y][x + 1] = 2;
				}
				--k;
			}
		}
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < m; ++j)
			{
				std::cout << T[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		int z = rand() % cover;
		while (z > 0)
		{
			int point = rand() % (2 * cover);
			if (point % 2 == 1)
				point--;

			int y = Stars[point], x = Stars[point + 1];
			if (Covered[y][x] == 1)
			{
				int dir = rand() % 4;

				if (dir == 0)
				{
					if (y != 0)
						T[y - 1][x] = "*";
				}
				if (dir == 1)
				{
					if (y != n - 1)
						T[y + 1][x] = "*";
				}

				if (dir == 2)
				{
					if (x != 0)
						T[y][x - 1] = "*";
				}

				if (dir == 3)
				{
					if (x != m - 1)
						T[y][x + 1] = "*";
				}
				Covered[y][x] = 3;
				--z;
			}
		}
	}
	else
	{
		if (k == max)
		{
			int one = rand() % 2;
			if (one == 1)
			{
				int	y = rand() % n, x = rand() % m;
				T[y][x] = "o";
			}
		}
		else
		{
			k = max - k;
			cover = k;

			if (mp)
			{
				while (k > 0)
				{
					int	y = rand() % n, x = rand() % m;
					if (x % 2 == 1)
					{
						x--;
					}
					if (Covered[y][x] == 0)
					{
						T[y][x] = T[y][x + 1] = "o";
						Covered[y][x] = Covered[y][x + 1] = 1;
						--k;
					}
				}

				int hit = 0;
				bool pp = false;
				int	y = rand() % n;
				if (y % 2 == 0)
				{
					pp = true;
				}
				while (hit != cover)
				{
					int	y = rand() % n;
					if (pp)
					{
						if (y % 2 == 0)
						{
							for (int i = 0; i < m; i+=2)
							{
								T[y][i] = "o";
							}
						}
						else
						{
							for (int i = 1; i < m; i += 2)
							{
								T[y][i] = "o";
							}
						}
					}
					else
					{
						if (y % 2 == 0)
						{
							for (int i = 1; i < m; i += 2)
							{
								T[y][i] = "o";
							}
						}
						else
						{
							for (int i = 0; i < m; i += 2)
							{
								T[y][i] = "o";
							}
						}
					}
					hit++;
				}
			}

			else if (np)
			{
				while (k > 0)
				{
					int	y = rand() % n, x = rand() % m;
					if (y % 2 == 1)
					{
						y--;
					}
					if (Covered[y][x] == 0)
					{
						T[y][x] = T[y + 1][x] = "o";
						Covered[y][x] = Covered[y + 1][x] = 1;
						--k;
					}
				}

				int hit = 0;
				bool pp = false;
				int	x = rand() % n;
				if (x % 2 == 0)
				{
					pp = true;
				}
				while (hit != cover)
				{
					int	x = rand() % n;
					if (pp)
					{
						if (x % 2 == 0)
						{
							for (int i = 0; i < m; i+=2)
							{
								T[i][x] = "o";
							}
						}
						else
						{
							for (int i = 1; i < m; i += 2)
							{
								T[i][x] = "o";
							}
						}
					}
					else
					{
						if (x % 2 == 0)
						{
							for (int i = 1; i < m; i += 2)
							{
								T[i][x] = "o";
							}
						}
						else
						{
							for (int i = 0; i < m; i += 2)
							{
								T[i][x] = "o";
							}
						}
					}
					hit++;
				}
			}

			else
			{
				while (k > 0)
				{
					int	y = rand() % n, x = rand() % m - 1;
					if (x % 2 == 1)
					{
						x--;
					}
					if (Covered[y][x] == 0)
					{
						T[y][x] = T[y][x + 1] = "o";
						Covered[y][x] = Covered[y][x + 1] = 1;
						--k;
					}
				}
				int hit = 0;
				bool pp = false;
				int	y = rand() % n;
				if (y % 2 == 0)
				{
					pp = true;
				}
				while (hit != cover)
				{
					int	y = rand() % n;
					if (pp)
					{
						if (y % 2 == 0)
						{
							for (int i = 0; i < m-1; i+=2)
							{
								T[y][i] = "o";
							}
						}
						else
						{
							for (int i = 1; i < m-1; i += 2)
							{
								T[y][i] = "o";
							}
						}
					}
					else
					{
						if (y % 2 == 0)
						{
							for (int i = 1; i < m-1; i += 2)
							{
								T[y][i] = "o";
							}
						}
						else
						{
							for (int i = 0; i < m-1; i += 2)
							{
								T[y][i] = "o";
							}
						}
					}
					hit++;
				}
			}
		}
	}

	return T;
}


int main()
{
	srand(time(NULL));

	int n = 5;
	int m = 6;
	int k = 15;
	std::string **T = generate(n, m, k, 2);

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			std::cout << T[i][j] << " ";
		}
		std::cout << std::endl;
	}


	return 0;
}
