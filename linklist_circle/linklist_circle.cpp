// linklist_circle.cpp : �������̨Ӧ�ó������ڵ㡣
#include"iostream"
#include"assert.h"
using namespace std;
typedef int DataType;
typedef struct LinkNode
{
	DataType data;
	LinkNode*next;
}linkNode, *pLinkNode;
typedef struct LinkList
{
	LinkNode*phead;
}LinkList, *pLinkList;
void Init_LinkList(pLinkList plist)       //��ʼ��  
{
	assert(plist);
	plist->phead = NULL;
}
pLinkNode Create_Node(DataType x)     //�����½��  
{
	pLinkNode newNode = (pLinkNode)malloc(sizeof(LinkNode));
	if (NULL == newNode)
	{
		printf("out of memory\n");
		exit(EXIT_FAILURE);
	}
	newNode->data = x;
	newNode->next = NULL;
	return newNode;
}
pLinkNode Check_Cycle(pLinkList plist)
{
	//�ж��Ƿ�������������򷵻�������
	pLinkNode fast = NULL;
	pLinkNode slow = NULL;
	assert(plist);
	fast = plist->phead;
	slow = plist->phead;
	while (fast&&fast->next)
	{
		fast = fast->next->next;
		slow = slow->next;
		if (fast == slow)
		{
			return fast;
		}
	}
	return NULL;
}
int Get_CircleLength(pLinkNode meet)
{
	//�󻷵ĳ���
	int count = 1;
	pLinkNode cur = meet;
	pLinkNode pmeet = meet;
	while (cur->next != pmeet)
	{
		count++;
		cur = cur->next;
	}
	return count;
}
void Push_back(pLinkList plist, DataType x)    //β��  
{
	//1.�ǿ����� 2.�н��  
	pLinkNode cur = NULL;
	pLinkNode newNode = NULL;
	assert(plist);
	cur = plist->phead;
	newNode = Create_Node(x);
	if (NULL == cur)           //�ǿ�����  
	{
		plist->phead = newNode;
	}
	else                      //�н��  
	{
		while (cur->next != NULL)    //�ҵ����һ�����  
		{
			cur = cur->next;
		}
		cur->next = newNode;
	}
}
pLinkNode Find_NUM(pLinkList plist, DataType x) //�ҽ��  
{
	pLinkNode cur = plist->phead;
	assert(plist);
	while (cur != NULL)
	{
		if (cur->data == x)
		{
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}
pLinkNode GetCircle_EntryNode(pLinkList plist, pLinkNode meet)
{
	//��ȡ������ڵ�
	pLinkNode front = plist->phead;
	pLinkNode back = meet;
	assert(plist);
	while (front != back)
	{
		front = front->next;
		back = back->next;
	}
	return front;
}

void test()
{
	int ptr = 0;
	pLinkNode ret = NULL;
	pLinkNode meet = NULL;
	LinkList plist;
	Init_LinkList(&plist);
	Push_back(&plist, 1);
	Push_back(&plist, 2);
	Push_back(&plist, 3);
	Push_back(&plist, 4);
	Push_back(&plist, 5);
	ret = Find_NUM(&plist, 5);  //���컷  
	ret->next = Find_NUM(&plist, 3);
	meet = Check_Cycle(&plist);
	if (meet != NULL)
	{
		printf("�����������ڵ�Ϊ��%d\n", meet->data);
		ptr = Get_CircleLength(meet);
		printf("���������ĳ���Ϊ��%d\n", ptr);
		ret = GetCircle_EntryNode(&plist, meet);
		printf("��������Ļ�����ڵ㣺%d\n", ret->data);
	}
}
int main()
{
	test();
	system("pause");
	return 0;
}