#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
typedef struct QNode {            //���ṹ
	int data;
	struct QNode *next;
}QNode;

typedef struct QNode *QueuePtr;

typedef struct {                //���е�����ṹ
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
		printf("1.�����\n2.������\n3.չʾ����\n������ѡ��:");
		scanf("%d", &choose);
		switch (choose)
		{
		case 1:
			printf("������Ҫ��ӵ����֣�");
			scanf("%d", &number);
			if (enQueue(&p, number))
				printf("��ӳɹ�!");
			else
				printf("���ʧ��!");
			break;
		case 2:
			number = deQueue(&p);
			if (number==-999)
				printf("����Ϊ��!");
			else
				printf("������Ԫ��:%d\n", number);
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
		printf("�ռ俪��ʧ��!\n");
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
		printf("�ռ俪��ʧ��!\n");
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