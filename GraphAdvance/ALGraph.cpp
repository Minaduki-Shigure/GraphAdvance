#include "ALGraph.h"
using namespace std;

int dis[6][6];
int dy[4] = { 0,1,0,-1 };
int dx[4] = { 1,0,-1,0 };
int maze[6][6] =
{
	{ 1,1,1,1,1,1 },
	{ 1,0,0,0,1,1 },
	{ 1,0,1,0,0,1 },
	{ 1,0,0,0,1,1 },
	{ 1,1,0,0,0,1 },
	{ 1,1,1,1,1,1 }
};

int visited[MAX_VERTEX_NUM];

ALGraph GraphInit(void)
{
	int i, k;
	ALGraph g;
	ArcNode *node;
	VertexType gef, gel;
	printf("顶点数：");
	scanf_s("%d", &g.VexNum);
	printf("边数：");
	scanf_s("%d", &g.ArcNum);
	for (i = 0; i<g.VexNum; i++)
	{
		g.Vertices[i].data = i;
		g.Vertices[i].FirstArc = NULL;
	}
	printf("请输入边。例如，0与2之间有边，则输入0 2 Enter\n");
	for (k = 0; k<g.ArcNum; k++)
	{
		printf("请输入第%d条边的信息：", k + 1);
		scanf_s("%d %d", &gef, &gel);
		node = (ArcNode*)malloc(sizeof(ArcNode));
		if (node == NULL)
			exit(-1);
		node->AdjVex = gel;
		node->NextArc = g.Vertices[gef].FirstArc;
		g.Vertices[gef].FirstArc = node;
		node = (ArcNode*)malloc(sizeof(ArcNode));
		if (node == NULL)
			exit(-1);
		node->AdjVex = gef;
		node->NextArc = g.Vertices[gel].FirstArc;
		g.Vertices[gel].FirstArc = node;
	}
	printf("Init success!\n");
	return g;
}

VertexType FindFistAdjVex(ALGraph g, int v)
{
	ArcNode *ptr = g.Vertices[v].FirstArc;
	if (ptr)
		return ptr->AdjVex;
	else
		return -1;
}

VertexType FindNextAdjVex(ALGraph g, int v, int w)
{
	ArcNode *ptr = g.Vertices[v].FirstArc;
	while (ptr)
	{
		if (ptr->AdjVex == w)
			break;
		ptr = ptr->NextArc;
	}
	if (ptr->AdjVex != w || !ptr->NextArc)
		return -1;
	return ptr->NextArc->AdjVex;
}

void DFS(ALGraph g, int v)
{
	ArcNode *ptr;
	visited[v] = 1;
	printf("%d ", g.Vertices[v].data);
	for (ptr = g.Vertices[v].FirstArc; ptr; ptr = ptr->NextArc)
	{
		if (!visited[ptr->AdjVex])
			DFS(g, ptr->AdjVex);
	}
	return;
}

void DFSTraverse(ALGraph g, int vex)
{
	for (int i = 0; i < g.VexNum; i++)
		visited[i] = 0;
	DFS(g, vex);
	for (int v = 0; v < g.VexNum; v++)
		if (!visited[v])
			DFS(g, v);
	putchar('\n');
	return;
}
/*
void widesort(ALGraph *p, int n)
{
	int t;
	headnode *s;
	CircQueue q = QueueInit(MAX_VERTEX_NUM);
	cout << p->graph[n - 1].number << "->";
	visit[n] = 1;
	inquene(q, n);
	while (quenempty(q))
	{
		t = outquene(q);
		s = p->graph[t - 1].next;
		while (s)
		{
			t = s->number;
			if (visit[t] == 0)
			{
				cout << p->graph[t - 1].number << "->";
				visit[t] = 1;
				inquene(q, t);
			}
			s = s->next;
		}

	}
}*/

void BFS(ALGraph g)
{
	for (int i = 0; i < g.VexNum; i++)
		visited[i] = 0;
	CircQueue q = QueueInit(MAX_VERTEX_NUM);
	int v;
	int u;
	ArcNode *ptr;
	for (v = 0; v < g.VexNum; v++)
	{
		if (!visited[v])
		{
			visited[v] = 1;
			printf("%d ", g.Vertices[v].data);
			EnQueue(&q, v);
			while (q.front != q.rear)
			{
				u = q.base[q.front];
				v = DeQueue(&q);
				for (ptr = g.Vertices[v].FirstArc; ptr; ptr = ptr->NextArc)
				{
					if (!visited[ptr->AdjVex])
					{
						visited[ptr->AdjVex] = 1;
						printf("%d ", g.Vertices[ptr->AdjVex].data);
						EnQueue(&q, ptr->AdjVex);
					}
				}
			}
		}
	}
	putchar('\n');
	return;
}

void MazeSolve(int x0, int y0, int x1, int y1)
{
	int i, j;
	queue<locate> que;
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 6; j++)
		{
			dis[i][j] = -1;
		}
	}
	locate a;
	a.x = x0; a.y = y0;
	que.push(a);
	dis[x0][y0] = 0;
	while (que.size())
	{
		a = que.front();
		cout << "(" << a.x << "," << a.y << ")" << endl;
		que.pop();
		int i;
		for (i = 0; i < 4; i++)
		{
			int nx, ny;
			nx = a.x + dx[i];
			ny = a.y + dy[i];
			if (0 <= nx && nx < 6 && 0 <= ny && ny < 6 && maze[nx][ny] != 1 && dis[nx][ny] == -1)
			{
				dis[nx][ny] = dis[a.x][a.y] + 1;
				a.x = nx;
				a.y = ny;
				que.push(a);
				if (nx == x1 && ny == y1) break;
			}
		}
		if (i != 4) break;
	}

}