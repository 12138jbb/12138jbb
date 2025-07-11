
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<stack>
#include"RBTree.h"
//红黑树的定义：
//红黑树和AVL树一样，都是平衡二叉搜索树，它们对二叉搜索树进行平衡化处理，
//只不过它两对平衡的定义不太一样

/*红黑树的四大性质：
1.红黑树首先得是一颗二叉搜索树，也就是说红黑树的任意一个节点都是大于左，
  小于右(口诀：左根右)
2.红黑树要求根节点和所有叶子节点都必须是黑色(口诀：根叶黑)
3.红黑树要求所有红色节点的左右孩子都必须是黑色(也就是不能出现连续的两个红色节点，即不红红)
4.红黑树要求任何一个节点到其叶子节点的所有路径上的黑色节点数量相同(路黑同)
*/

/*
在删除时，那些性质会被破坏：
1.左跟右，不会破坏
2.根叶黑，有肯能
3.不红红，有可能
4.路黑同，绝大多数情况下，破坏



*/


//AVL树要求任何一个节点的左右子树高度差小于等于1
//红黑树要求任何一个节点的左右子树高度差不超过2倍

//AVL树查找更高效，红黑树插入和删除更高效
//工具函数
//1.购买新节点
RBNode* BuyNode()
{
	RBNode* pnewnode = (RBNode*)malloc(sizeof(RBNode));
	if (pnewnode == NULL)
		exit(EXIT_FAILURE);
	memset(pnewnode, 0, sizeof(RBNode));
	//假如插入的新节点颜色是红色的话，则有一定概率插入后无需调整
	pnewnode->color = RED;
	return pnewnode;
}
//2.单左旋
RBNode* Left_Rotate(RBNode* Node)
{
	assert(Node != NULL);
	RBNode* father = Node->parent;
	RBNode* grandfather = Node->parent->parent;
	//让它爷左旋到它爸的左边，这里提前把冲突的节点处理掉
	//口诀：冲突的左孩变右孩
	grandfather->rightchild = father->leftchild;
	if (grandfather->rightchild != NULL)
	{
		grandfather->rightchild->parent = grandfather;
	}
	//此时它爷左旋到它爸的左边，没有障碍物，则直接挪动指针即可
	father->leftchild = grandfather;
	grandfather->parent = father;
	//返回新根节点(它爸)
	return father;
}
//3.单右旋
RBNode* Right_Rotate(RBNode* Node)
{
	assert(Node != NULL);
	RBNode* father = Node->parent;
	RBNode* grandfather = Node->parent->parent;

	//让它爷右旋到它爸的右边，这里提前把冲突的节点处理掉
	//口诀：冲突的右孩变左孩
	grandfather->leftchild = father->rightchild;
	if (grandfather->leftchild != NULL)
	{
		grandfather->leftchild->parent = grandfather;
	}

	//此时它爷右旋到它爸的右边，没有障碍物，则直接挪动指针即可
	father->rightchild = grandfather;
	grandfather->parent = father;
	//返回新根节点(它爸)
	return father;
}

//4.插入函数的通用平衡旋转函数  Node代表当前插入的节点，要进行平衡判断
//初版(不管parent指针)
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

	//3.执行到这，代表Node不是根节点，且Node节点违反了"不红红"，需要看其叔叔脸色行事
	//此时Node和Node它爸以及他爷3个节点肯定都存在

	//4.申请三个指针用来指向它爸，爷，叔叔
	RBNode* father = Node->parent;
	RBNode* grandfather = Node->parent->parent;
	//uncle有可能是空地址，所以判断uncle的颜色时，不能只判断其是否为RED
	RBNode* uncle = grandfather->leftchild == father ? grandfather->rightchild : grandfather->leftchild;

	//5.若叔是红色
	if (uncle != NULL && uncle->color == RED)
	{
		//叔父爷变色
		uncle->color = BLACK;
		father->color = BLACK;
		grandfather->color = RED;
		//把它爷当作新的插入节点，重新进行逻辑判断
		Insert_Adjust_Rotate(pTree, grandfather);
		return;
	}
	else//它叔是黑色：旋转+变色
	{
		//6.判断Node和它爸及它爷，这三个节点符合哪一个型号
		if (grandfather->leftchild == father)
		{
			if (father->leftchild == Node)//LL
			{
				//先变色
				grandfather->color = RED;
				father->color = BLACK;
				//再旋转
				//太爷节点有可能存在，有可能不存在
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
				//先左旋
				father->rightchild = Node->leftchild;
				Node->leftchild = father;
				grandfather->leftchild = Node;
				//再变色+右旋
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
				//先变色
				grandfather->color = RED;
				father->color = BLACK;
				//再旋转
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
				//先右旋
				father->leftchild = Node->rightchild;
				Node->rightchild = father;
				grandfather->rightchild = father;
				//再变色+左旋
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

//4.插入函数的通用平衡旋转函数  Node代表当前插入的节点，要进行平衡判断
//最终版(要管parent指针)
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

	//3.执行到这，代表Node不是根节点，且Node节点违反了"不红红"，需要看其叔叔脸色行事
	//此时Node和Node它爸以及他爷3个节点肯定都存在

	//4.申请三个指针用来指向它爸，爷，叔叔
	RBNode* father = Node->parent;
	RBNode* grandfather = Node->parent->parent;
	//uncle有可能是空地址，所以判断uncle的颜色时，不能只判断其是否为RED
	RBNode* uncle = grandfather->leftchild == father ? grandfather->rightchild : grandfather->leftchild;

	//5.若叔是红色
	if (uncle != NULL && uncle->color == RED)
	{
		//叔父爷变色
		uncle->color = BLACK;
		father->color = BLACK;
		grandfather->color = RED;
		//把它爷当作新的插入节点，重新进行逻辑判断
		Insert_Adjust_Rotate(pTree, grandfather);
		return;
	}
	else//它叔是黑色：旋转+变色
	{
		//6.判断Node和它爸及它爷，这三个节点符合哪一个型号
		if (grandfather->leftchild == father)
		{
			if (father->leftchild == Node)//LL
			{
				//先变色
				grandfather->color = RED;
				father->color = BLACK;
				//再旋转
				//太爷节点有可能存在，有可能不存在
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
				//先左旋
				father->rightchild = Node->leftchild;
				Node->leftchild = father;
				grandfather->leftchild = Node;
				//再变色+右旋
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
				//先变色
				grandfather->color = RED;
				father->color = BLACK;
				//再旋转
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
				//先右旋
				father->leftchild = Node->rightchild;
				Node->rightchild = father;
				grandfather->rightchild = father;
				//再变色+左旋
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

//5.删除函数的通用平衡旋转函数


//普通函数
//1.初始化
void Init_RBTree(RBTree* pTree)
{
	assert(pTree != NULL);
	pTree->root = NULL;
}
//2.插入
bool Insert_RBTree(RBTree* pTree, ELEMTYPE val)
{
	assert(pTree != NULL);
	//1.申请两个指针p和pp pp保存p的上一步
	RBNode* p = pTree->root;
	RBNode* pp = NULL;
	//2.进入循环，循环条件是p指向节点存在，且值不是我需要的
	while (p != NULL && p->val != val)
	{
		//3.根据和p的有效值的比较，让p走自己的左侧或右侧去遍历
		pp = p;
		p = val < p->val ? p->leftchild : p->rightchild;
	}

	//可能性1：如果p指向的节点存在
	if (p != NULL)
	{
		return true;
	}
	//可能性2：如果p指向的节点不存在
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

	if (pp->color == RED)//违反"不红红"
	{
		Insert_Adjust_Rotate(pTree, pnewnode);
	}
	return true;
}
//3.删除
bool Delete_RBTree(RBTree* pTree, ELEMTYPE val);
//4.查找
RBNode* Search_RBTree(RBTree* pTree, ELEMTYPE val)
{
	assert(pTree != NULL);
	RBNode* p = pTree->root;
	while (p != NULL && p->val != val)
		return p = val < p->val ? p->leftchild : p->rightchild;
}
//5.打印(中序遍历)
void Show_inOrder(RBNode* root)//递归
{
	if (root == NULL)
		return;
	Show_inOrder(root->leftchild);
	printf("%d ", root->val);
	Show_inOrder(root->rightchild);
}
void Show_inOrder2(RBTree* pTree)//非递归
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


//6.删除函数的通用平衡旋转函数
/*1.有2个孩子或一个孩子的节点，直接删除
2.
3.
*/
//红黑树单分支，不如改名，叫做待删除节点，只有左孩子和优化子
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


