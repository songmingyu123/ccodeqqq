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
//��������������
BSTree createBSTree(int *a, int len) {
	BSTree p = NULL;
	int flag = 0;
	for (size_t i = 0; i < len; i++) {
		//����ڵ�
		flag = insertBSNode(&p, a[i]);
	}
	return p;
}
//����ڵ�ǰ����Ҫ�жϸùؼ��ֽڵ��Ƿ��Ѿ����ڣ������ڣ���ֱ�ӽ������롣���򣬿����µĽڵ�
int insertBSNode(BSTree *bt, int key) {
	//�����ڵ㣬Ѱ��Ҫ����Ĺؼ��ֽڵ��Ƿ���ڡ�������searchBSTree()����1�����򷵻�0
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
		printf("Ҫ����Ľڵ� ��%d�� �Ѿ�����\n", key);
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
	//�нڵ��Ƿ�Ϊ��
	BSTree p = *bt;
	BSTree parents = NULL;
	BSTree precursor = NULL;
	BSTree temporary = NULL;//��ʱ��������Ҫɾ���Ľڵ�
	while (p != NULL) {
		//�ҵ�Ҫɾ���Ľڵ�
		if (p->key == key) {
			//pΪ�սڵ�
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
			//pֻ������
			else if (p->lChild != NULL && p->rChild == NULL) {
				//p��˫�׵�����
				if (parents->lChild == p) {
					parents->lChild = p->lChild;
					free(p);
					p = NULL;
				}
				//p��˫�׵��Һ���
				else {
					parents->rChild = p->lChild;
					free(p);
					p = NULL;
				}
			}
			//pֻ���Һ���
			else if (p->lChild == NULL && p->rChild != NULL) {
				//p��˫�׵�����
				if (parents->lChild == p) {
					parents->lChild = p->rChild;
					free(p);
					p = NULL;
				}
				//p��˫�׵��Һ���
				else {
					parents->rChild = p->rChild;
					free(p);
					p = NULL;
				}
			}
			//p��������Ҳ���Һ���
			else {
				//precursor��ʾҪɾ���ڵ��ǰ��
				precursor = p->lChild;
				//Ҫɾ���ڵ���������Һ��ӣ���ô��Ҫ�����ӵ��Һ��Ӵ���Ҫɾ���ڵ�
				if (precursor->rChild) {
					//ѭ��ֱ���ҵ�p��ֱ��ǰ��
					while (precursor->rChild != NULL) {
						precursor = precursor->rChild;
					}
					temporary = precursor;//�ݴ�Ҫɾ���Ľڵ�
					p->key = precursor->key;
					precursor = p->lChild;
					//�ٴ�ѭ������һ�ߣ��ҵ�Ҫɾ���Ľڵ��˫�ף�˫�׵ĺ�����ΪNULL
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
				//Ҫɾ���ڵ���������Һ��ӣ���ô��Ҫ������ֱ�Ӵ���Ҫɾ���ڵ㣬
				else {
					p->key = precursor->key;
					p->lChild = precursor->lChild;
					free(precursor);
					precursor = NULL;
				}

			}
			return 0;
		}
		//δ�ҵ�Ҫɾ���Ľڵ㣬ȥ��������
		else if (p->key < key) {
			parents = p;
			p = p->rChild;
		}
		//δ�ҵ�Ҫɾ���Ľڵ㣬ȥ��������
		else if (p->key > key) {
			parents = p;
			p = p->lChild;
		}
	}
}
