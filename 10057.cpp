/*********************************************************************
    程序名: AC自动机
    版权: 无
    作者: catten
    日期: 2021-01-27 11:44
    说明: #10057
*********************************************************************/
#include <iostream>
#include <bits/stdc++.h>
#include <cstdio>
#include <stack>
#include <queue>
#include <list>
#include <cmath>
using namespace std;
//#include <windows.h>
const int N = 5e5 + 5;
int ans, cnt, nxt[N], ch[N][30], bo[N], que[N];

void make(char *s)
{
	int u = 1, len = strlen(s);
	for (int i = 0; i < len; i++)
	{
		int c = s[i] - 'a';
		if (!ch[u][c])
		{
			ch[u][c] = ++cnt;
			memset(ch[cnt], 0, sizeof(ch[cnt]));
		}
		u = ch[u][c];
	}
	bo[u]++;
	return;
}

void bfs()
{
	for (int i = 0; i <= 25; i++)
	{
		ch[0][i] = 1;
	}
	que[1] = 1;
	nxt[1] = 0;
	for (int q1 = 1, q2 = 1; q1 <= q2; ++q1)
	{
		int u = que[q1];
		for (int i = 0; i <= 25; i++)
		{
			if (!ch[u][i])
			{
				ch[u][i] = ch[nxt[u]][i];
			}
			else
			{
				que[++q2] = ch[u][i];
				int v = nxt[u];
				nxt[ch[u][i]] = ch[v][i];
			}
		}
	}
	return;
}

void find(char *s)
{
	int u = 1, len = strlen(s), c, k;
	for (int i = 0; i <= len; i++)
	{
		c = s[i] - 'a';
		k = ch[u][c];
		while (k > 1)
		{
			ans += bo[k];
			bo[k] = 0;
			k = nxt[k];
		}
		u = ch[u][c];
	}
	return;
}

int main()
{
	int t, n;
	char s[N << 1];
	scanf("%d", &t);
	while (t--)
	{
		ans = 0;
		cnt = 1;
		memset(bo, 0, sizeof(bo));
		for (int i = 0; i < 26; i++)
		{
			ch[0][i] = 1, ch[1][i] = 0;
		}
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
		{
			scanf("%s", s);
			make(s);
		}
		bfs();
		scanf("%s", s);
		find(s);
		printf("%d\n", ans);
	}

	return 0;
}
