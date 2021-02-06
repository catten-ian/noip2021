/*********************************************************************
    程序名:数列区间最大值
    版权:无
    作者:catten
    日期: 2021-01-28 09:41
    说明:#10119
*********************************************************************/
#include <iostream>
#include <cstdio>
#include <stack>
#include <queue>
#include <list>
#include <algorithm>
using namespace std;

//#include <windows.h>
const int N = 1e6 + 5, LogN = 20;

int log[N];
int f[N][LogN + 5], a[N];
int n, m, x, y;
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
	}
	log[0] = -1;
	for (int i = 1; i <= n; i++)
	{
		f[i][0] = a[i];
		log[i] = log[i >> 1] + 1;
	}
	for (int j = 1; j <= LogN; j++)
	{
		for (int i = 1; i + (1 << j) - 1 <= n; i++)
		{
			f[i][j] = max(f[i][j - 1], f[i + (1 << j - 1)][j - 1]);
		}
	}
	while (m--)
	{
		scanf("%d%d", &x, &y);
		int s = log[y - x + 1];
		printf("%d\n", max(f[x][s], f[y - (1 << s) + 1][s]));
	}
	return 0;
}
