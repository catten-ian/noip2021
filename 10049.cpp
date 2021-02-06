/*********************************************************************
    程序名:Phone List
    版权:无
    作者: catten
    日期: 2021-01-27 10:08
    说明:Poj3630
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
const int N = 1e5 + 5;
const int Z = 10;
int T, n, tot;
int ch[N][Z];
bool bo[N];
char s[2 * Z];
void clear()
{
	memset(ch, 0, sizeof(ch));
	memset(bo, false, sizeof(bo));
}

bool insert(char *s)
{
	int len = strlen(s);
	int u = 1;
	bool flag = false;
	for (int i = 0; i < len; i++)
		{
			int c = s[i] - 48;
			if (!ch[u][c])
				{
					ch[u][c] = ++tot;
				}
			else if (i == len - 1)
				{
					flag = true;
				}
			u = ch[u][c];
			if (bo[u])
				{
					flag = true;
				}
		}
	bo[u] = true;
	return flag;
}

int main()
{
	scanf("%d", &T);
	while (T--)
		{
			scanf("%d", &n);
			tot = 1;
			clear();
			bool ans = false;
			for (int i = 1; i <= n; i++)
				{
					scanf("%s", s);
					if (insert(s))
						{
							ans = true;
						}
				}
			if (!ans)
				{
					puts("YES");
				}
			else
				{
					puts("NO");
				}
		}
	return 0;
}