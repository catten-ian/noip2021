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
using namespace std;
long long array1[105];

//#include <windows.h>
long long rand1()
{
	int ans = rand() - 1;
	ans = (ans << 15) + rand();
	if (rand() & 2)
		ans = -ans;
	return ans;
}

int main()
{
	freopen("data.md", "w", stdout);
	srand(3);
	int a = rand() % 50 + 50;
	int c = rand() % 50 + 50;
	cout << a << ' ' << c << endl << "array:" << endl;
	for (int i = 0; i < a; i++)
	{
		long long b = rand1() ;
		cout << b << endl;
		array1[i] = b;
	}
	cout << "problem:" << endl;
	//srand(8);
	for (int i = 0; i < c; i++)
	{
		int b = rand() % a;
		cout << array1[b] << endl;
	}
	cout << "end";
	return 0;
}
