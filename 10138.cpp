/*********************************************************************
    程序名:
    版权:
    作者:
    日期: 2021-01-28 09:41
    说明:
*********************************************************************/
#include <iostream>
#include <bits/stdc++.h>
#include <cstdio>
#include <stack>
#include <queue>
#include <list>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 31000;
const int M = 124000;
int n, m, Summ, Maxx;
int seg[N], rev[M], size[N], son[N], top[N], dep[N];
int sum[M], num[N], father[N], Max[M];
int first[N], next1[N], go[N];

void query(int k, int l, int r, int L, int R)
{
	if (L > r || R < l)
	{
		return ;
	}
	if (L <= l && r <= R)
	{
		Summ += sum[k];
		Maxx = max(Maxx, Max[k]);
		return ;
	}
	int mid = l + r >> 1, res = 0;
	if (mid >= L)
	{
		query(k << 1, l, mid, L, R);
	}
	if (mid + 1 <= R)
	{
		query((k << 1) + 1, mid + 1, r, L, R);
	}
}

void change(int k, int l, int r, int Val, int pos)
{
	if (pos > r || pos < l)
	{
		return ;
	}
	if (l == r && r == pos)
	{
		sum[k] = Val;
		Max[k] = Val;
		return ;
	}
	int mid = l + r >> 1;
	if (mid >= pos)
	{
		change(k << 1, l, mid, Val, pos);
	}
	if (mid + 1 <= pos)
	{
		change((k << 1) + 1, mid + 1, r, Val, pos);
	}
	sum[k] = sum[k << 1] + sum[(k << 1) + 1];
	Max[k] = max(Max[k << 1], Max[(k << 1) + 1]);
}

void dfs1(int u, int f)
{
	int e, v;
	size[u] = 1;
	father[u] = f;
	dep[u] = dep[f] + 1;
	for (e = first[u]; v = go[e], e; e = next1[e])
	{
		if (v != f)
		{
			dfs1(v, u);
			size[u] += size[v];
			if (size[v] > size[son[u]])
			{
				son[u] = v;
			}
		}
	}
}

void dfs2(int u, int f)
{
	int e, v;
	if (son[u])
	{
		seg[son[u]] = ++seg[0];
		top[son[u]] = top[u];
		rev[seg[0]] = son[u];
		dfs2(son[u], u);
	}
	for (e = first[u]; v = go[e], e; e = next1[e])
	{
		if (!top[v])
		{
			seg[v] = ++seg[0];
			rev[seg[0]] = v;
			top[v] = v;
			dfs2(v, u);
		}
	}
}

void build(int k, int l, int r)
{
	int mid = l + r >> 1;
	if (l == r)
	{
		Max[k] = sum[k] = num[rev[l]];
		return ;
	}
	build(k << 1, l, mid);
	build((k << 1) + 1, mid + 1, r);
	sum[k] = sum[k << 1] + sum[(k << 1) + 1];
	Max[k] = max(Max[k << 1], Max[(k << 1) + 1]);
}

inline int get()
{
	char c;
	int sign = 1;
	while ((c = getchar()) < '0' || c > '9')
	{
		if (c == '-')
		{
			sign = -1;
		}
	}
	int res = c - '0';
	while ((c = getchar()) >= '0' && c <= '9')
	{
		res = res * 10 + c - '0';
	}
	return res * sign;
}
int tot;

inline void add(int x, int y)
{
	next1[++tot] = first[x];
	first[x] = tot;
	go[tot] = y;
}

inline void insert(int x, int y)
{
	add(x, y);
	add(y, x);
}

inline void ask(int x, int y)
{
	int fx = top[x], fy = top[y];
	while (fx != fy)
	{
		if (dep[fx] < dep[fy])
		{
			swap(x, y);
			swap(fx, fy);
		}
		query(1, 1, seg[0], seg[fx], seg[x]);
		x = father[fx];
		fx = top[x];
	}
	if (dep[x] > dep[y])
	{
		swap(x, y);
	}
	query(1, 1, seg[0], seg[x], seg[y]);
}

int main()
{
	int i, j, k;
	n = get();
	for (int i = 1; i < n; i++)
	{
		insert(get(), get());
	}
	for (int i = 1; i <= n; i++)
	{
		num[i] = get();
	}
	dfs1(1, 0);
	seg[0] = seg[1] = top[1] = rev[1] = 1;
	dfs2(1, 0);
	build(1, 1, seg[0]);
	m = get();
	char sr[10];
	int u, v;
	for (int i = 1; i <= m; i++)
	{
		scanf("%s", sr + 1);
		u = get();
		v = get();
		if (sr[1] == 'C')
		{
			change(1, 1, seg[0], v, seg[u]);
		}
		else
		{
			Summ = 0;
			Maxx = -10000000;
			ask(u, v);
			if (sr[2] == 'M')
			{
				printf("%d\n", Maxx);
			}
			else
			{
				printf("%d\n", Summ);
			}
		}
	}
	return 0;
}


