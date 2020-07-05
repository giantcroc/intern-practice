#include<bits/stdc++.h>
using namespace std;
const int maxn = 1000;
int n;
int ve[maxn], vl[maxn];
struct Node
{
	int v, w;
}node;
int inDegree[maxn] = { 0 };
stack<int> topOrder;
vector<Node> G[maxn];
vector<int> pre[maxn];
bool topologicalSort()
{
	queue<int> q;
	int c = 0;
	for (int i = 0; i < n; i++)
	{
		if (inDegree[i] == 0)
			q.push(i);
	}
	while (!q.empty())
	{
		int u = q.front(); 
		c++;
		topOrder.push(u);
		q.pop();
		for (int i = 0; i < G[u].size(); i++)
		{
			int v = G[u][i].v, w = G[u][i].w;
			inDegree[v]--;
			if (inDegree[v] == 0)
				q.push(v);
			if (ve[u] + w > ve[v])ve[v] = ve[u] + w;
		}
	}
	return c == n ? true : false;
}
vector<int> path;
void DFS(int s, int e)
{
	if (s == e)
	{
		path.push_back(s);
		for (int i = path.size() - 1; i >= 0; i--)
		{
			printf("%d", path[i]);
			if (i > 0)printf("->");
			else printf("\n");
		}
		path.pop_back();
		return;
	}
	path.push_back(e);
	for (int i = 0; i < pre[e].size(); i++)
	{
		DFS(s, pre[e][i]);
	}
	path.pop_back();
}
int criticalPath()
{
	fill(ve, ve + n, 0);
	if (!topologicalSort())
	{
		return -1;
	}
	fill(vl, vl + n, ve[n - 1]);
	while (!topOrder.empty())
	{
		int u = topOrder.top();
		topOrder.pop();
		for (int i = 0; i < G[u].size(); i++)
		{
			int v = G[u][i].v, w = G[u][i].w;
			if (vl[v] - w < vl[u])
			{
				vl[u] = vl[v] - w;
			}
		}
	}
	printf("所有的关键活动如下所示：\n");
	for (int u = 0; u < n; u++)
	{
		for (int i = 0; i < G[u].size(); i++)
		{
			int v = G[u][i].v, w = G[u][i].w;
			int e = ve[u], l = vl[v] - w;
			if (e == l)
			{
				printf("%d->%d\n", u + 1, v + 1);//输出时加1以还原输入时做出的改变
				pre[v + 1].push_back(u + 1);
			}
		}
	}
	printf("所有的关键路径如下所示：\n");
	DFS(1, n);
	return ve[n - 1];
}
 
int main()
{
	freopen("i.txt", "r", stdin);//键盘输入流重定向为i.txt文件输入流
	int m;
	scanf("%d %d", &n,&m);//n为点数，m为边数
	int a, b, w;
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d%d", &a, &b, &w);//a、b为事件，w为ab这条边所表示的活动耗费的时间
		node.v = b-1; node.w = w;
        inDegree[b-1]++;
		G[a-1].push_back(node);//实际存储时为了方便a、b都减1
	}
	printf("关键路径长度为：%d\n",criticalPath());
	return 0;
}
/*
输入为（即i.txt内容）：
9 11
1 2 6
1 3 4
1 4 5
2 5 1
3 5 1
4 6 2
5 7 9
5 8 7
6 8 4
7 9 2
8 9 4
*/