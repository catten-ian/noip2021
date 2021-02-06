/*********************************************************************
    程序名:单点修改，区间查询
    版权:无
    作者:catten
    日期: 2021-01-28 09:41
    说明:#130
*********************************************************************/
#include <iostream>
#include <bits/stdc++.h>
#include <cstdio>
#include <stack>
#include <queue>
#include <list>
#include <cmath>
using namespace std;

inline int read()
{
	char ch;
	while ((ch = getchar()) < '0' || ch > '9');
	int res = ch - 48;
	while ((ch = getchar()) >= '0' && ch <= '9')
		res = res * 10 + ch - 48;
	return res;
}
const int N = 1e5 + 5;
int n, m;
long long sum[N * 4];

void change(int k, int l, int r, int p, int v)
{
	if (r < p || l > p)
		return ;
	if (l == r && l == p)
	{
		sum[k] += v;
		return ;
	}
	int mid = (l + r) / 2;
	change(k * 2, l, mid, p, v);
	change(k * 2 + 1, mid + 1, r, p, v);
	sum[k] = sum[k * 2] + sum[k * 2 + 1];
}

long long query(int k, int l, int r, int x, int y)
{
	if (y < l || x > r)
	{
		return 0;
	}
	if (l >= x && r <= y)
	{
		return sum[k];
	}
	int mid = (l + r) / 2;
	long long res = 0;
	res = query(k * 2, l, mid, x, y);
	res += query(k * 2 + 1, mid + 1, r, x, y);
	return res;
}

//#include <windows.h>
int main()
{
	n = read();
	m = read();
	for (int i = 1; i <= n; i++)
	{
		int r = read();
		change(1, 1, n, i, r);
	}
	for (int i = 1; i <= m; i++)
	{
		int k = read();
		int l = read();
		int r = read();
		if (k == 1)
		{
			change(1, 1, n, l, r);
		}
		else
			printf("%lld\n", query(1, 1, n, l, r));
	}

	return 0;
}
