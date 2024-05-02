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
	BSTree q = NULL;//�������
	BSTree p = NULL;//�������
	if (T->data.key == key_delete)
	{
		q = T;//��¼
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
void UBSTree(BSTree T,BSTree p,BSTree q)//���¶�������������,UpdataBSTree()
{
	q = T;//��¼
	p = q->rchild;
	T = q->rchild;
	T->lchild = q->lchild;
	q = q->rchild;
}
BSTree BalanceBSTree(BSTree T,HighType* lflag,HighType* rflag)//�����ж��Ƿ�ΪAVl(ƽ�������)
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
//̫����,ûʲô��ע�͵�
//CreatBTree()������E://����,��Ϊ���ж���,����Ҫ���һЩif()�����������������ж����Ĵ���
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
//ȫ�õݹ�д���Ǵ��Է籩��,Delete���½ṹ��ʱ������������������,Ц������,��д�껹�����гɾ͸е�,�Ͼ�Ҳ������̫��