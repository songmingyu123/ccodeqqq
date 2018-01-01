/*
 * @Author: songmingyu 
 * @Date: 2018-01-01 14:03:08 
 * @Last Modified by: songmingyu
 * @Last Modified time: 2018-01-01 14:47:58
 */

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
void statisticsBSTree(BSTree);
int n0=0;
int n1=0;
int n2=0;
int main() {
	int a[] = { 30,15,28,20,24,10,12,68,35,50,46,55 };
	//int a[] = { 50,55,36,35,30 };
	int num = 0;
	BSTree bt = createBSTree(a, sizeof(a) / sizeof(a[0]));
	inOrderTree(bt);
	printf("\n");
	//scanf("%d", &num);
	//deleteBSNode(&bt,num);
	//inOrderTree(bt);
    statisticsBSTree(bt);
    printf("n0:%d\nn1:%d\nn2:%d\n",n0,n1,n2);
	return 0;
}

BSTree createBSTree(int *a, int len) {
	BSTree p = NULL;
	int flag = 0;
	for (size_t i = 0; i < len; i++) {
		flag = insertBSNode(&p, a[i]);
	}
	return p;
}
int insertBSNode(BSTree *bt, int key) {
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
		printf("the key %d exists.\n", key);
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
	BSTree p = *bt;
	BSTree parents = NULL;
	BSTree precursor = NULL;
	BSTree temporary = NULL;
	while (p != NULL) {
		if (p->key == key) {
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
			else if (p->lChild != NULL && p->rChild == NULL) {
				if (parents->lChild == p) {
					parents->lChild = p->lChild;
					free(p);
					p = NULL;
				}
				else {
					parents->rChild = p->lChild;
					free(p);
					p = NULL;
				}
			}
			else if (p->lChild == NULL && p->rChild != NULL) {
				if (parents->lChild == p) {
					parents->lChild = p->rChild;
					free(p);
					p = NULL;
				}
				else {
					parents->rChild = p->rChild;
					free(p);
					p = NULL;
				}
			}
			else {
				precursor = p->lChild;
				if (precursor->rChild) {
					while (precursor->rChild != NULL) {
						precursor = precursor->rChild;
					}
					temporary = precursor;
					p->key = precursor->key;
					precursor = p->lChild;
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
				else {
					p->key = precursor->key;
					p->lChild = precursor->lChild;
					free(precursor);
					precursor = NULL;
				}

			}
			return 0;
		}
		else if (p->key < key) {
			parents = p;
			p = p->rChild;
		}
		else if (p->key > key) {
			parents = p;
			p = p->lChild;
		}
	}
}

void statisticsBSTree(BSTree bt){
    if(!bt->lChild && !bt->rChild){
        ++n0;
        return;
    }
    else if(bt->lChild && bt->rChild){
        ++n2;
        statisticsBSTree(bt->lChild);
        statisticsBSTree(bt->rChild);
    }
    else if(bt->lChild){
        ++n1;
        statisticsBSTree(bt->lChild);
    }
    else{
        ++n1;
        statisticsBSTree(bt->rChild);
    }
    return; 
}