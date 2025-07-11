#pragma once

typedef int ELEMTYPE;
typedef enum { RED, BLACK }TYPE_COLOR;
//红黑树的节点定义
typedef struct RBNode
{
	ELEMTYPE val;
	struct RBNode* leftchild;
	struct RBNode* parent;
	struct RBNode* rightchild;
	//bool color;//true=红 false=黑
	TYPE_COLOR color;
}RBNode;

//红黑树辅助节点定义
typedef struct
{
	RBNode* root;
}RBTree;

//工具函数
//1.购买新节点
RBNode* BuyNode();
//2.单左旋
RBNode* Left_Rotate(RBNode* Node);
//3.单右旋
RBNode* Right_Rotate(RBNode* Node);
//4.插入函数的通用平衡旋转函数  Node代表当前插入的节点，要进行平衡判断
void Insert_Adjust_Rotate(RBTree* pTree, RBNode* Node);
//5.删除函数的通用平衡旋转函数


//普通函数
//1.初始化
void Init_RBTree(RBTree* pTree);
//2.插入
bool Insert_RBTree(RBTree* pTree, ELEMTYPE val);
//3.删除
bool Delete_RBTree(RBTree* pTree, ELEMTYPE val);
//4.查找
RBNode* Search_RBTree(RBTree* pTree, ELEMTYPE val);
//5.打印(中序遍历)
void Show_inOrder(RBNode* root);//递归
void Show_inOrder2(RBTree* pTree);//非递归
#pragma once
