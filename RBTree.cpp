
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<stack>
#include"RBTree.h"
//������Ķ��壺
//�������AVL��һ��������ƽ����������������ǶԶ�������������ƽ�⻯����
//ֻ����������ƽ��Ķ��岻̫һ��

/*��������Ĵ����ʣ�
1.��������ȵ���һ�Ŷ�����������Ҳ����˵�����������һ���ڵ㶼�Ǵ�����
  С����(�ھ��������)
2.�����Ҫ����ڵ������Ҷ�ӽڵ㶼�����Ǻ�ɫ(�ھ�����Ҷ��)
3.�����Ҫ�����к�ɫ�ڵ�����Һ��Ӷ������Ǻ�ɫ(Ҳ���ǲ��ܳ���������������ɫ�ڵ㣬�������)
4.�����Ҫ���κ�һ���ڵ㵽��Ҷ�ӽڵ������·���ϵĺ�ɫ�ڵ�������ͬ(·��ͬ)
*/

/*
��ɾ��ʱ����Щ���ʻᱻ�ƻ���
1.����ң������ƻ�
2.��Ҷ�ڣ��п���
3.����죬�п���
4.·��ͬ�������������£��ƻ�



*/


//AVL��Ҫ���κ�һ���ڵ�����������߶Ȳ�С�ڵ���1
//�����Ҫ���κ�һ���ڵ�����������߶Ȳ����2��

//AVL�����Ҹ���Ч������������ɾ������Ч
//���ߺ���
//1.�����½ڵ�
RBNode* BuyNode()
{
	RBNode* pnewnode = (RBNode*)malloc(sizeof(RBNode));
	if (pnewnode == NULL)
		exit(EXIT_FAILURE);
	memset(pnewnode, 0, sizeof(RBNode));
	//���������½ڵ���ɫ�Ǻ�ɫ�Ļ�������һ�����ʲ�����������
	pnewnode->color = RED;
	return pnewnode;
}
//2.������
RBNode* Left_Rotate(RBNode* Node)
{
	assert(Node != NULL);
	RBNode* father = Node->parent;
	RBNode* grandfather = Node->parent->parent;
	//����ү���������ֵ���ߣ�������ǰ�ѳ�ͻ�Ľڵ㴦���
	//�ھ�����ͻ���󺢱��Һ�
	grandfather->rightchild = father->leftchild;
	if (grandfather->rightchild != NULL)
	{
		grandfather->rightchild->parent = grandfather;
	}
	//��ʱ��ү���������ֵ���ߣ�û���ϰ����ֱ��Ų��ָ�뼴��
	father->leftchild = grandfather;
	grandfather->parent = father;
	//�����¸��ڵ�(����)
	return father;
}
//3.������
RBNode* Right_Rotate(RBNode* Node)
{
	assert(Node != NULL);
	RBNode* father = Node->parent;
	RBNode* grandfather = Node->parent->parent;

	//����ү���������ֵ��ұߣ�������ǰ�ѳ�ͻ�Ľڵ㴦���
	//�ھ�����ͻ���Һ�����
	grandfather->leftchild = father->rightchild;
	if (grandfather->leftchild != NULL)
	{
		grandfather->leftchild->parent = grandfather;
	}

	//��ʱ��ү���������ֵ��ұߣ�û���ϰ����ֱ��Ų��ָ�뼴��
	father->rightchild = grandfather;
	grandfather->parent = father;
	//�����¸��ڵ�(����)
	return father;
}

//4.���뺯����ͨ��ƽ����ת����  Node����ǰ����Ľڵ㣬Ҫ����ƽ���ж�
//����(����parentָ��)
void Insert_Adjust_Rotate(RBTree* pTree, RBNode* Node)
{
	assert(pTree != NULL);
	if (Node->parent == NULL)
	{
		Node->color = BLACK;
		return;
	}

	if (Node->parent->color == BLACK)
	{
		return;
	}

	//3.ִ�е��⣬����Node���Ǹ��ڵ㣬��Node�ڵ�Υ����"�����"����Ҫ����������ɫ����
	//��ʱNode��Node�����Լ���ү3���ڵ�϶�������

	//4.��������ָ������ָ�����֣�ү������
	RBNode* father = Node->parent;
	RBNode* grandfather = Node->parent->parent;
	//uncle�п����ǿյ�ַ�������ж�uncle����ɫʱ������ֻ�ж����Ƿ�ΪRED
	RBNode* uncle = grandfather->leftchild == father ? grandfather->rightchild : grandfather->leftchild;

	//5.�����Ǻ�ɫ
	if (uncle != NULL && uncle->color == RED)
	{
		//�常ү��ɫ
		uncle->color = BLACK;
		father->color = BLACK;
		grandfather->color = RED;
		//����ү�����µĲ���ڵ㣬���½����߼��ж�
		Insert_Adjust_Rotate(pTree, grandfather);
		return;
	}
	else//�����Ǻ�ɫ����ת+��ɫ
	{
		//6.�ж�Node�����ּ���ү���������ڵ������һ���ͺ�
		if (grandfather->leftchild == father)
		{
			if (father->leftchild == Node)//LL
			{
				//�ȱ�ɫ
				grandfather->color = RED;
				father->color = BLACK;
				//����ת
				//̫ү�ڵ��п��ܴ��ڣ��п��ܲ�����
				RBNode* great_grandfather = grandfather->parent;
				RBNode* ptr = Right_Rotate(Node);
				if (great_grandfather == NULL)
				{
					pTree->root = ptr;
				}
				else
				{
					if (great_grandfather->val > ptr->val)
					{
						great_grandfather->leftchild = ptr;
					}
					else
					{
						great_grandfather->rightchild = ptr;
					}
				}
				return;
			}
			else//LR
			{
				//������
				father->rightchild = Node->leftchild;
				Node->leftchild = father;
				grandfather->leftchild = Node;
				//�ٱ�ɫ+����
				Node->color = BLACK;
				grandfather->color = RED;
				RBNode* great_grandfather = grandfather->parent;
				RBNode* ptr = Right_Rotate(father);
				if (great_grandfather == NULL)
				{
					pTree->root = ptr;
				}
				else
				{
					if (ptr->val < great_grandfather->val)
					{
						great_grandfather->leftchild = ptr;
					}
					else
					{
						great_grandfather->rightchild = ptr;
					}
				}
				return;
			}
		}


		if (grandfather->rightchild == father)
		{
			if (father->rightchild == Node)//RR
			{
				//�ȱ�ɫ
				grandfather->color = RED;
				father->color = BLACK;
				//����ת
				RBNode* great_grandfather = grandfather->parent;
				RBNode* ptr = Left_Rotate(Node);
				if (great_grandfather == NULL)
				{
					pTree->root = ptr;
				}
				else
				{
					if (ptr->val < grandfather->val)
					{
						grandfather->leftchild = ptr;
					}
					else
					{
						grandfather->rightchild = ptr;
					}
				}
				return;
			}
			else//RL
			{
				//������
				father->leftchild = Node->rightchild;
				Node->rightchild = father;
				grandfather->rightchild = father;
				//�ٱ�ɫ+����
				Node->color = BLACK;
				grandfather->color = RED;
				RBNode* great_grandfather = grandfather->parent;
				RBNode* ptr = Left_Rotate(father);
				if (great_grandfather == NULL)
				{
					pTree->root = ptr;
				}
				else
				{
					if (ptr->val < grandfather->val)
					{
						grandfather->leftchild = ptr;
					}
					else
					{
						grandfather->rightchild = ptr;
					}
				}
				return;
			}
		}
	}
}

//4.���뺯����ͨ��ƽ����ת����  Node����ǰ����Ľڵ㣬Ҫ����ƽ���ж�
//���հ�(Ҫ��parentָ��)
void Insert_Adjust_Rotate_2(RBTree* pTree, RBNode* Node)
{
	assert(pTree != NULL);
	if (Node->parent == NULL)
	{
		Node->color = BLACK;
		return;
	}

	if (Node->parent->color == BLACK)
	{
		return;
	}

	//3.ִ�е��⣬����Node���Ǹ��ڵ㣬��Node�ڵ�Υ����"�����"����Ҫ����������ɫ����
	//��ʱNode��Node�����Լ���ү3���ڵ�϶�������

	//4.��������ָ������ָ�����֣�ү������
	RBNode* father = Node->parent;
	RBNode* grandfather = Node->parent->parent;
	//uncle�п����ǿյ�ַ�������ж�uncle����ɫʱ������ֻ�ж����Ƿ�ΪRED
	RBNode* uncle = grandfather->leftchild == father ? grandfather->rightchild : grandfather->leftchild;

	//5.�����Ǻ�ɫ
	if (uncle != NULL && uncle->color == RED)
	{
		//�常ү��ɫ
		uncle->color = BLACK;
		father->color = BLACK;
		grandfather->color = RED;
		//����ү�����µĲ���ڵ㣬���½����߼��ж�
		Insert_Adjust_Rotate(pTree, grandfather);
		return;
	}
	else//�����Ǻ�ɫ����ת+��ɫ
	{
		//6.�ж�Node�����ּ���ү���������ڵ������һ���ͺ�
		if (grandfather->leftchild == father)
		{
			if (father->leftchild == Node)//LL
			{
				//�ȱ�ɫ
				grandfather->color = RED;
				father->color = BLACK;
				//����ת
				//̫ү�ڵ��п��ܴ��ڣ��п��ܲ�����
				RBNode* great_grandfather = grandfather->parent;
				RBNode* ptr = Right_Rotate(Node);
				if (great_grandfather == NULL)
				{
					pTree->root = ptr;
					ptr->parent = NULL;
				}
				else
				{
					if (great_grandfather->val > ptr->val)
					{
						great_grandfather->leftchild = ptr;
						ptr->parent = great_grandfather;
					}
					else
					{
						great_grandfather->rightchild = ptr;
						ptr->parent = great_grandfather;
					}
				}
				return;
			}
			else//LR
			{
				//������
				father->rightchild = Node->leftchild;
				Node->leftchild = father;
				grandfather->leftchild = Node;
				//�ٱ�ɫ+����
				Node->color = BLACK;
				grandfather->color = RED;
				RBNode* great_grandfather = grandfather->parent;
				RBNode* ptr = Right_Rotate(father);
				if (great_grandfather == NULL)
				{
					pTree->root = ptr;
				}
				else
				{
					if (ptr->val < great_grandfather->val)
					{
						great_grandfather->leftchild = ptr;
					}
					else
					{
						great_grandfather->rightchild = ptr;
					}
				}
				return;
			}
		}


		if (grandfather->rightchild == father)
		{
			if (father->rightchild == Node)//RR
			{
				//�ȱ�ɫ
				grandfather->color = RED;
				father->color = BLACK;
				//����ת
				RBNode* great_grandfather = grandfather->parent;
				RBNode* ptr = Left_Rotate(Node);
				if (great_grandfather == NULL)
				{
					pTree->root = ptr;
				}
				else
				{
					if (ptr->val < grandfather->val)
					{
						great_grandfather->leftchild = ptr;
					}
					else
					{
						great_grandfather->rightchild = ptr;
					}
					ptr->parent = grandfather;
				}
				return;
			}
			else//RL
			{
				//������
				father->leftchild = Node->rightchild;
				Node->rightchild = father;
				grandfather->rightchild = father;
				//�ٱ�ɫ+����
				Node->color = BLACK;
				grandfather->color = RED;
				RBNode* great_grandfather = grandfather->parent;
				RBNode* ptr = Left_Rotate(father);
				if (great_grandfather == NULL)
				{
					pTree->root = ptr;
					ptr->parent = NULL;
				}
				else
				{
					if (ptr->val < grandfather->val)
						great_grandfather->leftchild = ptr;
					else
						great_grandfather->rightchild = ptr;
					ptr->parent = grandfather;
				}
				return;
			}
		}
	}
}

//5.ɾ��������ͨ��ƽ����ת����


//��ͨ����
//1.��ʼ��
void Init_RBTree(RBTree* pTree)
{
	assert(pTree != NULL);
	pTree->root = NULL;
}
//2.����
bool Insert_RBTree(RBTree* pTree, ELEMTYPE val)
{
	assert(pTree != NULL);
	//1.��������ָ��p��pp pp����p����һ��
	RBNode* p = pTree->root;
	RBNode* pp = NULL;
	//2.����ѭ����ѭ��������pָ��ڵ���ڣ���ֵ��������Ҫ��
	while (p != NULL && p->val != val)
	{
		//3.���ݺ�p����Чֵ�ıȽϣ���p���Լ��������Ҳ�ȥ����
		pp = p;
		p = val < p->val ? p->leftchild : p->rightchild;
	}

	//������1�����pָ��Ľڵ����
	if (p != NULL)
	{
		return true;
	}
	//������2�����pָ��Ľڵ㲻����
	RBNode* pnewnode = BuyNode();
	pnewnode->val = val;

	if (pp == NULL)
	{
		pTree->root = pnewnode;
		pnewnode->color = BLACK;
		return true;
	}
	if (val < pp->val)
	{
		pp->leftchild = pnewnode;
		pnewnode->parent = pp;
	}
	else
	{
		pp->rightchild = pnewnode;
		pnewnode->parent = pp;
	}

	if (pp->color == RED)//Υ��"�����"
	{
		Insert_Adjust_Rotate(pTree, pnewnode);
	}
	return true;
}
//3.ɾ��
bool Delete_RBTree(RBTree* pTree, ELEMTYPE val);
//4.����
RBNode* Search_RBTree(RBTree* pTree, ELEMTYPE val)
{
	assert(pTree != NULL);
	RBNode* p = pTree->root;
	while (p != NULL && p->val != val)
		return p = val < p->val ? p->leftchild : p->rightchild;
}
//5.��ӡ(�������)
void Show_inOrder(RBNode* root)//�ݹ�
{
	if (root == NULL)
		return;
	Show_inOrder(root->leftchild);
	printf("%d ", root->val);
	Show_inOrder(root->rightchild);
}
void Show_inOrder2(RBTree* pTree)//�ǵݹ�
{
	assert(pTree->root != NULL);
	std::stack<RBNode*> st;
	st.push(pTree->root);
	bool tag = true;
	while (!st.empty())
	{
		while (tag && st.top()->leftchild != NULL)
			st.push(st.top()->leftchild);
		RBNode* p = st.top();
		st.pop();

		printf("%d ", p->val);

		if (p->rightchild != NULL)
		{
			st.push(p->rightchild);
			tag = true;
		}
		else
		{
			tag = false;
		}
	}
}


//6.ɾ��������ͨ��ƽ����ת����
/*1.��2�����ӻ�һ�����ӵĽڵ㣬ֱ��ɾ��
2.
3.
*/
//���������֧�����������������ɾ���ڵ㣬ֻ�����Ӻ��Ż���
bool Delete_RBTree(RBTree* pTree, ELEMTYPE val)
{



}

int main()
{
	RBTree head;
	Insert_RBTree(&head, 17);
	Insert_RBTree(&head, 18);
	Insert_RBTree(&head, 23);
	Insert_RBTree(&head, 34);
	Insert_RBTree(&head, 27);
	Insert_RBTree(&head, 15);
	Insert_RBTree(&head, 9);
	Insert_RBTree(&head, 6);
	Insert_RBTree(&head, 8);
	Insert_RBTree(&head, 5);
	Insert_RBTree(&head, 25);
	Show_inOrder(head.root);
	return 0;
}


