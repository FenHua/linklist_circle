// linklist_circle.cpp : 定义控制台应用程序的入口点。
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
void Init_LinkList(pLinkList plist)       //初始化  
{
	assert(plist);
	plist->phead = NULL;
}
pLinkNode Create_Node(DataType x)     //创建新结点  
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
	//判断是否带环，若带环则返回相遇点
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
	//求环的长度
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
void Push_back(pLinkList plist, DataType x)    //尾插  
{
	//1.是空链表 2.有结点  
	pLinkNode cur = NULL;
	pLinkNode newNode = NULL;
	assert(plist);
	cur = plist->phead;
	newNode = Create_Node(x);
	if (NULL == cur)           //是空链表  
	{
		plist->phead = newNode;
	}
	else                      //有结点  
	{
		while (cur->next != NULL)    //找到最后一个结点  
		{
			cur = cur->next;
		}
		cur->next = newNode;
	}
}
pLinkNode Find_NUM(pLinkList plist, DataType x) //找结点  
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
	//获取环的入口点
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
	ret = Find_NUM(&plist, 5);  //构造环  
	ret->next = Find_NUM(&plist, 3);
	meet = Check_Cycle(&plist);
	if (meet != NULL)
	{
		printf("带环的相遇节点为：%d\n", meet->data);
		ptr = Get_CircleLength(meet);
		printf("带环链表环的长度为：%d\n", ptr);
		ret = GetCircle_EntryNode(&plist, meet);
		printf("带环链表的环的入口点：%d\n", ret->data);
	}
}
int main()
{
	test();
	system("pause");
	return 0;
}