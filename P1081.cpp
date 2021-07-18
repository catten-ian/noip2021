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

unsigned int a[MAX_LEN];
unsigned int b[MAX_LEN];
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

void preProcess()
{
	for (int i = 0; i <= n; i++)
		cities[i].id = i;
	qsort(cities, n, sizeof(city_t), cmp);
	for (int i = 0; i <= n; i++)
	{
		idx_arr[cities[i].id] = i;
	}
	cities[n].h = (long long) 10e10;
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
	printCities();
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
		a[idx] = min_i2;
		b[idx] = min_i1;
		ax[idx] = min2;
		bx[idx] = min1;
		printf("id:%d,idx:%d, a %d, b %d\n", i, idx, a[idx], b[idx]);
	}
	b[n] = n;
	a[n] = n;
	ax[n] = bx[n] = cities[n].h;
	for (int i = 0; i < n; i++)
	{
		printf("i:%d, %d,%d, h:%lld,%lld\n", cities[i].id, cities[a[i]].id, cities[b[i]].id,
		       ax[i], bx[i])
		;
	}
}

int f[18][MAX_LEN];
long long fax[18][MAX_LEN];
long long fbx[18][MAX_LEN];

void build_2tree()
{
	for (int i = 0; i < n; i++)
	{
		f[0][i] = a[i];
		fax[0][i] = ax[i];
		fbx[0][i] = 0;
		f[1][i] = b[a[i]];
		fax[1][i] = fax[0][i];
		fbx[1][i] = bx[f[0][i]];
	}
	for (int level = 2; level < 17; level++)
	{
		for (int i = 0; i < n; i++)
		{
			f[level][i] = f[level - 1][f[level - 1][i]];
			fax[level][i] = fax[level - 1][i] + fax[level - 1][f[level - 1][i]];
			fbx[level][i] = fbx[level - 1][i] + fbx[level - 1][f[level - 1][i]];
		}
	}
}

void getab(long long &a, long long &b, long long x, int s)
{
	a = 0;
	b = 0;
	for (int i = 17; i >= 0; i--)
	{
		if (a + b + fax[i][s] + fbx[i][s] < x)
		{
			a += fax[i][s];
			b += fbx[i][s];
			s = f[i][s];
		}
	}
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
		if (b == 0)
			ratio = 1e15;
		else
		{
			ratio = 1.0 * a / b;
		}
		if (min_ratio >= ratio)
		{
			min_ratio = ratio;
			min_i = i;
		}
	}
	printf("%d\n", cities[min_i].id);
	for (int i = 0; i < m; i++)
	{
		long long a, b;
		getab(a, b, x[i], s[i]);
		printf("%lld %lld\n", a, b);
	}
	return 0;
}



