#pragma once

typedef int ELEMTYPE;
typedef enum { RED, BLACK }TYPE_COLOR;
//������Ľڵ㶨��
typedef struct RBNode
{
	ELEMTYPE val;
	struct RBNode* leftchild;
	struct RBNode* parent;
	struct RBNode* rightchild;
	//bool color;//true=�� false=��
	TYPE_COLOR color;
}RBNode;

//����������ڵ㶨��
typedef struct
{
	RBNode* root;
}RBTree;

//���ߺ���
//1.�����½ڵ�
RBNode* BuyNode();
//2.������
RBNode* Left_Rotate(RBNode* Node);
//3.������
RBNode* Right_Rotate(RBNode* Node);
//4.���뺯����ͨ��ƽ����ת����  Node����ǰ����Ľڵ㣬Ҫ����ƽ���ж�
void Insert_Adjust_Rotate(RBTree* pTree, RBNode* Node);
//5.ɾ��������ͨ��ƽ����ת����


//��ͨ����
//1.��ʼ��
void Init_RBTree(RBTree* pTree);
//2.����
bool Insert_RBTree(RBTree* pTree, ELEMTYPE val);
//3.ɾ��
bool Delete_RBTree(RBTree* pTree, ELEMTYPE val);
//4.����
RBNode* Search_RBTree(RBTree* pTree, ELEMTYPE val);
//5.��ӡ(�������)
void Show_inOrder(RBNode* root);//�ݹ�
void Show_inOrder2(RBTree* pTree);//�ǵݹ�
#pragma once
