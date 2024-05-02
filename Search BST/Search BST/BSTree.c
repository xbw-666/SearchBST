#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef int KeyType;
typedef int InfoType;
typedef int DeleteType;
typedef int HighType;
typedef struct
{
	KeyType key;
	InfoType otherinfo;
}ElemType;
typedef struct BSTNode
{
	ElemType data;
	struct BSTNode* lchild, * rchild;
}BSTNode, * BSTree;
int* lflag = 0;
int* rflag = 0;
HighType* Maxlflag = 0;
HighType* Maxrflag = 0;
void CreatBSTree(BSTree T)
{
	T = (BSTree*)malloc(sizeof(BSTree));
	if (T == NULL)
		exit(0);
	else
	{
		scanf_s("%d", &T->data.key);
		CreatBSTree(T->lchild);
		CreatBSTree(T->rchild);
	}
}
BSTree SearchBST(BSTree T, KeyType key)
{
	if ((T == NULL) || (T->data.key == key))
	{
		return T;
	}
	else
	{
		if (key < T->data.key)
		{
			return SearchBST(T->lchild, &key);
		}
		else
		{
			return SearchBST(T->rchild, &key);
		}
	}
}
BSTree InitBST(BSTree T, BSTree q)
{
	if (T == NULL)
	{
		T = (BSTree*)malloc(sizeof(BSTree));
		T = q;
	}
	else
	{
		if (q->data.key < T->data.key)
		{
			return SearchBST(T->lchild, q);
		}
		else
		{
			return SearchBST(T->rchild, q);
		}
	}
}
BSTree SearchBST(BSTree T, KeyType key)
{
	if ((T == NULL) || (T->data.key == key))
	{
		return T;
	}
	else
	{
		if (key < T->data.key)
		{
			return SearchBST(T->lchild, &key);
		}
		else
		{
			return SearchBST(T->rchild, &key);
		}
	}
}
void PrintBSTree(BSTree T)
{
	if (T == NULL)
		exit(0);
	else
	{
		printf("%d", T->data.key);
		CreatBSTree(T->lchild);
		CreatBSTree(T->rchild);
	}
}
BSTree DeleteBST(BSTree T, DeleteType key_delete)
{
	BSTree q = NULL;//辅助结点
	BSTree p = NULL;//辅助结点
	if (T->data.key == key_delete)
	{
		q = T;//记录
		p = q->rchild;
		T = NULL;
		if ((T->lchild==NULL) && (T->rchild==NULL))
		{
			exit(0);
		}
		else
		{
			T = q->rchild;
			T->lchild = q->lchild;
			q = q->rchild;
			Updata(T,p,q);
		}
		//free(p&&q);
		free(p);
		free(q);
		PrintBSTree(T);
	}
	else
	{
		if (key_delete < T->data.key)
		{
			return SearchBST(T->lchild, &key_delete);
		}
		else
		{
			return SearchBST(T->rchild, &key_delete);
		}
	}
}
void UBSTree(BSTree T,BSTree p,BSTree q)//更新二叉排序树函数,UpdataBSTree()
{
	q = T;//记录
	p = q->rchild;
	T = q->rchild;
	T->lchild = q->lchild;
	q = q->rchild;
}
BSTree BalanceBSTree(BSTree T,HighType* lflag,HighType* rflag)//用来判断是否为AVl(平衡二叉树)
{
	if (T == NULL)
	{
		return;
	}
	else
	{
		BalanceBSTree(T->lchild, &lflag, &rflag);
		*lflag++;
		BalanceBSTree(T, &lflag, &rflag);
		if (*lflag > *rflag)
			*Maxlflag = *lflag;
		else
			*Maxlflag = *rflag;
		BalanceBSTree(T->rchild, &lflag, &rflag);
		*rflag++;
		if (*lflag > *rflag)
			*Maxrflag = *lflag;
		else
			*Maxrflag = *rflag;
		if (DetermineBSTree(T));
		else
			exit(0);
	}
}
int DetermineBSTree(BSTree T)
{
	if ((abs(*Maxlflag - *Maxrflag) == 1) || (*Maxlflag == *Maxrflag))
	{
		printf("This is BalanceBSTree");
		return 1;
	}
	else
	{
		printf("This not is BalanceBSTree");
		return 0;
	}
}
//太简单了,没什么可注释的
//CreatBTree()函数在E://里找,因为是判断树,所以要多加一些if()条件来完成这个二叉判断树的创建
void main()
{
	int key = 0;
	int key_delete = 0;
	BSTree T=NULL;
	BSTree q = NULL;
	printf("please input k what number:>");
	CreatBSTree(T);
	SearchBST(T, &key);
	InitBST(T, q);
	DeleteBST(T, &key_delete);
	BalanceBSTree(T, &lflag, &rflag);
	DetermineBSTree(T);
}
//全用递归写真是大脑风暴啊,Delete更新结构的时候让我想起来了链表,笑死个人,但写完还是蛮有成就感的,毕竟也不能算太简单