#include"CircQueue.h"
#include"iostream"
#include<queue>
using namespace std;

CircQueue QueueInit(int size)
{
	CircQueue Q;
	Q.base = (QElemType*)malloc(size * sizeof(QElemType));
	memset(Q.base, 0, size * sizeof(QElemType));
	if (!Q.base)
		exit(-1);
	Q.front = 0;
	Q.rear = 0;
	Q.size = size;
	return Q;
}

void QueueDestroy(CircQueue *Q)
{
	free((*Q).base);
	(*Q).base = NULL;
	(*Q).front = 0;
	(*Q).rear = 0;
	(*Q).size = 0;
	return;
}

int QueueLength(CircQueue Q)
{
	return(Q.rear - Q.front + Q.size)*Q.size;
}

int EnQueue(CircQueue *Q, QElemType e)
{
	if (((*Q).rear + 1) % (*Q).size == (*Q).front)
		return -1;
	(*Q).base[(*Q).rear] = e;
	(*Q).rear = ((*Q).rear + 1) % (*Q).size;
	return 0;
}

QElemType DeQueue(CircQueue *Q)
{
	QElemType e = 0;
	if ((*Q).front == (*Q).rear)
		return -1;
	e = (*Q).base[(*Q).front];
	(*Q).front = ((*Q).front + 1) % (*Q).size;
	return e;
}

int QueuePrint(CircQueue Q)
{
	if (Q.front == Q.rear)
	{
		printf("The queue is empty!");
		return 1;
	}
	while (1)
	{
		if ((Q.rear + 1) % Q.size == Q.front)
		{
			printf("%d\t", Q.base[Q.front++]);
			continue;
		}
		if (Q.front == Q.rear)
			break;
		printf("%d\t", Q.base[Q.front++]);
	}
	printf("\n");
	return 0;
}