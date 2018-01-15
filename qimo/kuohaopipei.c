#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include <stdlib.h>
#include<string.h>

enum node_type{ NUM, OP };
typedef struct Node{
	char operation;
	enum node_type type;
	struct Node *next;
}Node;

typedef struct Stack{
	struct Node *top;
	int length;
}Stack;

void judge(const char[]);
void Push(Stack *,Node *);
void InitStack(Stack *);
void Pop(Stack *);

int main()
{
	char expression[100];
	scanf("%s", expression);
	judge(expression);
	//getch();
	return 0;
}

void judge(const char expression[])
{
	Node *p;
	Stack opration;
	Stack *opra;
	opra = &opration;
	InitStack(opra);
	for (size_t i = 0; i < strlen(expression); i++)
	{
		if (expression[i] == '(' || expression[i] == '[' || expression[i] == '{')
		{
			p = (Node *)malloc(sizeof(Node));
			p->operation = expression[i];
			p->type = OP;
			Push(opra, p);
		}
		else if (expression[i] == ')' || expression[i] == ']' || expression[i] == '}')
		{
			//while (opra->top->operation != '(' && opra->top->operation != '[' && opra->top->operation != '{')
			//{
			//	Pop(opra);
			//}
			switch (expression[i])
			{
			case ')':
				if ( opra->length == 0 || opra->top->operation != '(')
				{
					printf("no");
					return 0;
				}
				else
				{
					Pop(opra);
				}
				break;
			case ']':
				if (opra->length == 0 || opra->top->operation != '[')
				{
					printf("no");
					return 0;
				}
				else
				{
					Pop(opra);
				}
				break;
			case '}':
				if (opra->length == 0 || opra->top->operation != '{')
				{
					printf("no");
					return 0;
				}
				else
				{
					Pop(opra);
				}
				break;
			default:
				break;
			}
		}
	}
	if (opra->top == NULL)
	{
		printf("yes");
	}
	else
	{
		printf("no");
	}

}

void InitStack(Stack *ps)
{
	ps->length = 0;
	ps->top = NULL;
}

void Push(Stack *opra, Node *p)
{
	p->next = opra->top;
	opra->top = p;
	opra->length++;
}

void Pop(Stack *opra)
{
	if (opra->top)
	{
		opra->top = opra->top->next;
		opra->length--;
	}
	else
	{
		printf("no");
		exit(0);
	}
}
