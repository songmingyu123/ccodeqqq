#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
typedef struct QNode {            //结点结构
	int data;
	struct QNode *next;
}QNode;

typedef struct QNode *QueuePtr;

typedef struct {                //队列的链表结构
	QueuePtr rear;
	QueuePtr front;
}LinkQueue;

int initQueue(LinkQueue *);
int enQueue(LinkQueue *, int);
int deQueue(LinkQueue *);

int main()
{
	LinkQueue p;
	int choose = 0;
	int number = 0;
	initQueue(&p);
	while (1)
	{
		printf("1.入队列\n2.出队列\n3.展示队列\n请输入选项:");
		scanf("%d", &choose);
		switch (choose)
		{
		case 1:
			printf("请输入要入队的数字：");
			scanf("%d", &number);
			if (enQueue(&p, number))
				printf("入队成功!");
			else
				printf("入队失败!");
			break;
		case 2:
			number = deQueue(&p);
			if (number==-999)
				printf("队列为空!");
			else
				printf("出队列元素:%d\n", number);
			break;
		default:
			break;
		}
			
	}

}

int initQueue(LinkQueue *p)
{
	QueuePtr q = NULL;
	q = (QueuePtr)malloc(sizeof(QNode));
	if (!q)
	{
		printf("空间开辟失败!\n");
		getch();
		exit(0);
	}
	p->front = p->rear = q;
	p->front->next = NULL;
}

int enQueue(LinkQueue *p, int number)
{
	QNode *q = NULL;
	q = (QueuePtr)malloc(sizeof(QNode));
	if (!q)
	{
		printf("空间开辟失败!\n");
		getch();
		exit(0);
	}
	q->data = number;
	q->next = NULL;
	p->rear->next = q;
	p->rear = q;
	return 1;
}

int deQueue(LinkQueue *p)
{
	QueuePtr q = NULL;
	int number = 0;
	if (p->front == p->rear)
		return -999;
	q = p->front->next;
	if (q == p->rear)
		p->front = p->rear;
	else
		p->front->next = q->next;

	number = q->data;
	free(q);

	return number;
}