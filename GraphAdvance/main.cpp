#include<iostream>  
#include<stdlib.h>  

using namespace std;

#define MAX 20

class ArcNode {
public:
	int adjvex; //�洢������ֹλ��  
	ArcNode *nextarc;
};

class VNode {
public:
	char data;  //�����Ϣ  
	ArcNode *firsarc;//��һ�����ߵĵ�ַ  
};
//����ͼ�������Ϣ  

class Graph {
public:
	VNode Node[MAX];
	int arcnum;//���ߵĸ���  
	int vexnum;//����ĸ���  
};
//�������������  

void dfs(Graph G, int v);
void bfs(Graph G);
int visited[MAX];//���dfs�����飬����û�б����ʹ�  
int book[MAX]; //���bfs�����飬����û�б����ʹ�  

int main()
{
	//�洢ͼ�������Ϣ  
	Graph G;
	int i;
	for (i = 1; i <= MAX; i++)
	{
		G.Node[i].firsarc = NULL;
	}
	cout << "����ͼ�Ľ������ͻ��ĸ���\n";
	cin >> G.vexnum;
	cin >> G.arcnum;
	cout << "�������㰴˳�����¶�Ӧ��Ϣ��";
	for (i = 1; i <= G.vexnum; i++)
	{
		cin >> G.Node[i].data;
	}
	cout << "���뻡����Ϣ\n";
	char start, end; //���满����ʼ�㣬��ֹ��  
	int s, t;//�洢��ʼ�㣬��ֹ��ı��  
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
			while (p->nextarc)       //ע������ֻ����p->nextarc,Ҫ��Ȼ��p=NULL���˳���û��������  
			{
				p = p->nextarc;
			}
			p->nextarc = ptr;
		}
		cout << "sss\n";

		ptr->nextarc = NULL;
	}
	/*//������
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
	for (i = 1; i <= G.vexnum; i++) //��ֹͼ�ǲ���ͨ��ͼ   
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
	//������У����ҶԶ��н��г�ʼ��  
	char queue[MAX] = { '\0' };
	int front = 0, rear = 1, i, j;
	ArcNode*ptr;
	for (j = 1; j <= G.vexnum; j++)  //����Ϊ�˷�ֹͼ������ͨ��  
	{
		if (book[j] != 1)
		{
			cout << G.Node[j].data;  //���������֮ǰ������з������  
			book[j] = 1;
			queue[rear++] = G.Node[j].data;
			//�Ӷ��㿪ʼ�����Ͻ��г��ӣ�������������йص��յ���ӣ�ֱ������Ϊ��  
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