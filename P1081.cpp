#include <bits/stdc++.h>
#include <stdlib.h>
#define MAX_LEN	100005
unsigned int n;

struct city_t
{
	long long h;
	int id;
	int next, prev;
} cities[MAX_LEN];
unsigned int x0;
unsigned int m;
unsigned int s[MAX_LEN], x[MAX_LEN];

void read_data()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &cities[i].h);
	scanf("%d", &x0);
	scanf("%d", &m);
	for (int i = 0; i < m; i++)
		scanf("%d%d", &s[i], &x[i]);
}

unsigned int an[MAX_LEN];
unsigned int bn[MAX_LEN];
long long ax[MAX_LEN], bx[MAX_LEN];


int idx_arr[MAX_LEN];

int cmp(const void *a, const void *b)
{
	return ((city_t *)a)->h - ((city_t *)b)->h;
}

void printCities()
{
	for (int i = 0; i < n; i++)
	{
		printf("citi idx:%d, id:%d, h:%lld, n:%d,p:%d\n",
		       i, cities[i].id, cities[i].h,
		       cities[i].next, cities[i].prev
		      );
	}
}

void printAnBn()
{
	printf("an:");
	for (int i = 0; i <= n; i++)
	{
		printf("(%d,%d),", cities[i].id, cities[an[i]].id);
	}
	printf("\n");
	printf("bn:");
	for (int i = 0; i <= n; i++)
	{
		printf("(%d,%d),", cities[i].id, cities[bn[i]].id);
	}
	printf("\n");
}

void preProcess()
{
	for (int i = 0; i <= n; i++)
		cities[i].id = i;
	qsort(cities, n, sizeof(city_t), cmp);
	for (int i = 0; i <= n; i++)
	{
		idx_arr[cities[i].id] = i;
	}
	cities[n].h = (long long) 1e11;
	cities[n].next = n;
	cities[n].prev = n;
	cities[0].next = 1;
	cities[0].prev = n;
	cities[n - 1].next = n;
	cities[n - 1].prev = n - 2;
	for (int i = 1; i < n - 1; i++)
	{
		cities[i].prev = i - 1;
		cities[i].next = i + 1;
	}
	// printCities();
	// build a and b
	for (int i = 0; i < n; i++)
	{
		int idx = idx_arr[i];
		int min1, min2, min_i1 = n, min_i2 = n;
		min_i1 = cities[idx].prev;
		min1 = llabs(cities[idx].h - cities[min_i1].h);
		min_i2 = cities[min_i1].prev;
		min2 = llabs(cities[idx].h - cities[min_i2].h);
		int idx1 = cities[idx].next;
		long long dif = llabs(cities[idx1].h - cities[idx].h);
		if (dif < min1)
		{
			min2 = min1;
			min_i2 = min_i1;
			min1 = dif;
			min_i1 = idx1;
			idx1 = cities[idx1].next;
			dif = llabs(cities[idx1].h - cities[idx].h);
			if (dif < min2)
			{
				min_i2 = idx1;
				min2 = dif;
			}
		}
		else
		{
			// printf("dif:%lld,min2:%lld\n", dif, min2);
			if (dif < min2)
			{
				min2 = dif;
				min_i2 = idx1;
			}
		}
		an[idx] = min_i2;
		bn[idx] = min_i1;
		ax[idx] = min2;
		bx[idx] = min1;
		//printf("id:%d,idx:%d, a %d, b %d\n", i, idx, an[idx], bn[idx]);
		// remove idx from current list
		if (cities[idx].next != n)
			cities[cities[idx].next].prev = cities[idx].prev;
		if (cities[idx].prev != n)
			cities[cities[idx].prev].next = cities[idx].next;
	}
	bn[n] = n;
	an[n] = n;
	ax[n] = bx[n] = cities[n].h;
	/*
	for (int i = 0; i < n; i++)
	{
		printf("i:%d, %d,%d, h:%lld,%lld\n", cities[i].id, cities[a[i]].id, cities[b[i]].id,
		       ax[i], bx[i]
		      );
	}
	*/
}

int f[18][MAX_LEN];
long long fax[18][MAX_LEN];
long long fbx[18][MAX_LEN];

void printArrF(int k)
{
	for (int level = 0; level < k; level++)
	{
		printf("level %d:", level);
		for (int i = 0; i <= n; i++)
		{
			printf("(%d,%d),", cities[i].id, cities[f[level][i]].id);
		}
		printf("\n");
	}
}

void printFax(int k)
{
	for (int level = 0; level < k; level++)
	{
		printf("fa level %d:", level);
		for (int i = 0; i <= n; i++)
		{
			printf("(%d,%lld),", cities[i].id, fax[level][i]);
		}
		printf("\n");
	}
}

void printFbx(int k)
{
	for (int level = 0; level < k; level++)
	{
		printf("fb level %d:", level);
		for (int i = 0; i <= n; i++)
		{
			printf("(%d,%lld),", cities[i].id, fbx[level][i]);
		}
		printf("\n");
	}
}

void build_2tree()
{
	// printAnBn();
	for (int i = 0; i <= n; i++)
	{
		f[0][i] = an[i];
		fax[0][i] = ax[i];
		fbx[0][i] = 0;
		f[1][i] = bn[an[i]];
		fax[1][i] = fax[0][i];
		fbx[1][i] = bx[f[0][i]];
	}
	for (int level = 2; level < 17; level++)
	{
		for (int i = 0; i <= n; i++)
		{
			f[level][i] = f[level - 1][f[level - 1][i]];
			fax[level][i] = fax[level - 1][i] + fax[level - 1][f[level - 1][i]];
			fbx[level][i] = fbx[level - 1][i] + fbx[level - 1][f[level - 1][i]];
			if (fax[level][i] > 1e10)
				fax[level][i] = 1e10;
			if (fbx[level][i] > 1e10)
				fbx[level][i] = 1e10;
		}
	}
	//printArrF(5);
	//printFax(5);
	//printFbx(5);
}

void getab(long long &a, long long &b, long long x, int sc)
{
	a = 0;
	b = 0;
	// s = idx_arr[s];
	// printf("sc:%d,id:%d\n", sc, cities[sc].id);
	for (int i = 16; i >= 0; i--)
	{
		if ( (a + b + fax[i][sc] + fbx[i][sc] <= x) && (f[i][sc] < n) )
		{
			a += fax[i][sc];
			b += fbx[i][sc];
			//printf("level:%d,a:%lld,b:%lld,ins:%d,outs:%d\n", i,
			//       a, b, cities[sc].id, cities[f[i][sc]].id);
			sc = f[i][sc];
		}
	}
	// printf("x:%lld, s:")
}

int main()
{
	freopen("p1081_test1.in", "r", stdin);
	read_data();
	preProcess();
	build_2tree();
	// ready to output
	int min_i;
	double ratio, min_ratio = 1e15;
	for (int i = 0; i < n; i++)
	{
		long long a, b;
		int sx = i;
		getab(a, b, x0, sx);
		//ratio = (b < 1LL) ? 1e14 : (1.0 * a ) / b;
		if (b < 1LL)
		{
			ratio = 1e14;
			//printf("%lld<1,ratio=%le\n", b, ratio);
		}
		else
		{
			ratio = (1.0 * a ) / b;
			//printf("%lld,ratio=%le\n", b, ratio);
		}
		if (min_ratio >= ratio)
		{
			min_ratio = ratio;
			min_i = i;
		}
	}
	printf("%d\n", cities[min_i].id + 1);
	for (int i = 0; i < m; i++)
	{
		long long a, b;
		int idx = idx_arr[s[i] - 1];
		getab(a, b, x[i], idx);
		printf("%lld %lld\n", a, b);
	}
	return 0;
}



