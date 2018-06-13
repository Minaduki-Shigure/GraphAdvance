#include<iostream>  
#include<stdlib.h>  

using namespace std;

#define MAX 20

class ArcNode {
public:
	int adjvex; //存储弧的终止位置  
	ArcNode *nextarc;
};

class VNode {
public:
	char data;  //结点信息  
	ArcNode *firsarc;//第一个弧边的地址  
};
//定义图的相关信息  

class Graph {
public:
	VNode Node[MAX];
	int arcnum;//弧边的个数  
	int vexnum;//定点的个数  
};
//主函数相关内容  

void dfs(Graph G, int v);
void bfs(Graph G);
int visited[MAX];//标记dfs的数组，看有没有被访问过  
int book[MAX]; //标记bfs的数组，看有没有被访问过  

int main()
{
	//存储图的相关信息  
	Graph G;
	int i;
	for (i = 1; i <= MAX; i++)
	{
		G.Node[i].firsarc = NULL;
	}
	cout << "输入图的结点个数和弧的个数\n";
	cin >> G.vexnum;
	cin >> G.arcnum;
	cout << "输入各结点按顺序编号下对应信息：";
	for (i = 1; i <= G.vexnum; i++)
	{
		cin >> G.Node[i].data;
	}
	cout << "输入弧的信息\n";
	char start, end; //储存弧的起始点，终止点  
	int s, t;//存储起始点，终止点的编号  
	int j;
	ArcNode*ptr, *p;
	for (i = 1; i <= G.arcnum; i++)
	{
		cin >> start;

		cin >> end;

		getchar();
		for (j = 1; j <= G.vexnum; j++)
		{
			if (start == G.Node[j].data)
				s = j;
			if (end == G.Node[j].data)
				t = j;
		}
		ptr = new ArcNode;
		ptr->adjvex = t;

		if (G.Node[s].firsarc == NULL)
		{
			G.Node[s].firsarc = ptr;
		}
		else
		{
			p = G.Node[s].firsarc;
			while (p->nextarc)       //注意这里只能是p->nextarc,要不然，p=NULL再退出就没有意义了  
			{
				p = p->nextarc;
			}
			p->nextarc = ptr;
		}
		cout << "sss\n";

		ptr->nextarc = NULL;
	}
	/*//输出检查
	for (i = 1; i <= G.vexnum; i++)
	{
	cout << G.Node[i].data << endl;
	p=G.Node[i].firsarc;
	while (p)
	{
	cout << "ppp\n";
	cout << p->adjvex << endl;
	p = p->nextarc;
	}
	}*/
	for (i = 1; i <= G.vexnum; i++) //防止图是不连通的图   
	{
		if (visited[i] != 1)
			dfs(G, i);
	}
	cout << "\n";
	bfs(G);
	system("pause");


	return 0;
}
void dfs(Graph G, int v)
{
	cout << G.Node[v].data;
	visited[v] = 1;
	ArcNode*p = G.Node[v].firsarc;
	while (p)
	{
		if (visited[p->adjvex] == 0)
			dfs(G, p->adjvex);
		else
			p = p->nextarc;
	}

}
void bfs(Graph G)
{
	//定义队列，并且对队列进行初始化  
	char queue[MAX] = { '\0' };
	int front = 0, rear = 1, i, j;
	ArcNode*ptr;
	for (j = 1; j <= G.vexnum; j++)  //这是为了防止图不是联通的  
	{
		if (book[j] != 1)
		{
			cout << G.Node[j].data;  //在其进队列之前对其进行访问输出  
			book[j] = 1;
			queue[rear++] = G.Node[j].data;
			//从定点开始，不断进行出队，输出，将定点有关的终点入队，直到队列为空  
			while (rear - 1 != front)
			{
				for (i = 1; queue[front + 1] != G.Node[i].data; i++);
				front++;
				ptr = G.Node[i].firsarc;

				while (ptr)
				{
					if (book[ptr->adjvex] != 1)
					{
						cout << G.Node[ptr->adjvex].data;
						book[ptr->adjvex] = 1;
						queue[rear++] = G.Node[ptr->adjvex].data;
					}

					ptr = ptr->nextarc;
				}
			}
		}
	}

}