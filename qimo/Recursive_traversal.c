#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
typedef struct BSTNode
{
	int key;
	struct BSTNode *lChild;
	struct BSTNode *rChild;
}BSTNode, *BSTree;

BSTNode *createBSTree(int *, int);
int insertBSNode(BSTree*, int);
void inOrderTree(BSTree);
int deleteBSNode(BSTree*, int);

int main() {
	//int a[] = { 30,15,28,20,24,10,12,68,35,50,46,55 };
	int a[] = { 50,55,36,35,30 };
	int num = 0;
	BSTree bt = createBSTree(a, sizeof(a) / sizeof(a[0]));
	inOrderTree(bt);
	printf("\n");
	scanf("%d", &num);
	deleteBSNode(&bt,num);
	inOrderTree(bt);
	getch();
	return 0;
}
//创建二叉排序树
BSTree createBSTree(int *a, int len) {
	BSTree p = NULL;
	int flag = 0;
	for (size_t i = 0; i < len; i++) {
		//插入节点
		flag = insertBSNode(&p, a[i]);
	}
	return p;
}
//插入节点前，需要判断该关键字节点是否已经存在，若存在，就直接结束插入。否则，开辟新的节点
int insertBSNode(BSTree *bt, int key) {
	//遍历节点，寻找要插入的关键字节点是否存在。若存在searchBSTree()返回1，否则返回0
	if (!(*bt)) {
		BSTree p = (BSTree)malloc(sizeof(BSTNode));
		p->key = key;
		p->lChild = p->rChild = NULL;
		*bt = p;
		return 1;
	}
	else if (key < (*bt)->key) {
		return insertBSNode(&((*bt)->lChild), key);
	}
	else if (key > (*bt)->key) {
		return insertBSNode(&((*bt)->rChild), key);
	}
	else {
		printf("要插入的节点 “%d” 已经存在\n", key);
		return 0;
	}
}

void inOrderTree(BSTree bt) {
	if (!bt) {
		return;
	}
	else {
		inOrderTree(bt->lChild);
		printf("%d ", bt->key);
		inOrderTree(bt->rChild);
	}
}

int deleteBSNode(BSTree *bt, int key) {
	//判节点是否为空
	BSTree p = *bt;
	BSTree parents = NULL;
	BSTree precursor = NULL;
	BSTree temporary = NULL;//暂时用来保存要删除的节点
	while (p != NULL) {
		//找到要删除的节点
		if (p->key == key) {
			//p为空节点
			if (p->lChild == NULL && p->rChild == NULL) {
				if (parents->lChild && parents->lChild->key == key) {
					free(p);
					parents->lChild = NULL;
				}
				else {
					free(p);
					parents->rChild = NULL;
				}
				return 0;
			}
			//p只有左孩子
			else if (p->lChild != NULL && p->rChild == NULL) {
				//p是双亲的左孩子
				if (parents->lChild == p) {
					parents->lChild = p->lChild;
					free(p);
					p = NULL;
				}
				//p是双亲的右孩子
				else {
					parents->rChild = p->lChild;
					free(p);
					p = NULL;
				}
			}
			//p只有右孩子
			else if (p->lChild == NULL && p->rChild != NULL) {
				//p是双亲的左孩子
				if (parents->lChild == p) {
					parents->lChild = p->rChild;
					free(p);
					p = NULL;
				}
				//p是双亲的右孩子
				else {
					parents->rChild = p->rChild;
					free(p);
					p = NULL;
				}
			}
			//p既有左孩子也有右孩子
			else {
				//precursor表示要删除节点的前驱
				precursor = p->lChild;
				//要删除节点的左孩子有右孩子，那么就要用左孩子的右孩子代替要删除节点
				if (precursor->rChild) {
					//循环直到找到p的直接前驱
					while (precursor->rChild != NULL) {
						precursor = precursor->rChild;
					}
					temporary = precursor;//暂存要删除的节点
					p->key = precursor->key;
					precursor = p->lChild;
					//再次循环遍历一边，找到要删除的节点的双亲，双亲的孩子置为NULL
					while (precursor->rChild && precursor->rChild != temporary) {
						precursor = precursor->rChild;
					}
					if (precursor->rChild && precursor->rChild->lChild != NULL) {
						precursor->rChild = precursor->rChild->lChild;
					}
					else {
						precursor->rChild = NULL;
					}
					free(temporary);
					temporary = NULL;
				}
				//要删除节点的左孩子无右孩子，那么就要用左孩子直接代替要删除节点，
				else {
					p->key = precursor->key;
					p->lChild = precursor->lChild;
					free(precursor);
					precursor = NULL;
				}

			}
			return 0;
		}
		//未找到要删除的节点，去找右子树
		else if (p->key < key) {
			parents = p;
			p = p->rChild;
		}
		//未找到要删除的节点，去找左子树
		else if (p->key > key) {
			parents = p;
			p = p->lChild;
		}
	}
}