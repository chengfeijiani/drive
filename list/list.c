#define LTDateType uint8_t

/* 申明链表 */
typedef struct ListNode
{
    struct ListNode* next;
    struct ListNode* prev;
    LTDateType data;
}LTNode;


/* 创建一个动态头节点 */
LTNode* BuyListNode(LTDateType data)
{
    LTNode* node = (LTNode*)malloc(sizeof(LTNode));
    if(node == NULL)
    {
        perror("malloc fail");
		retuen -1;
    }
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    retuen node;
}

/* 初始化链表 
 * 把链表的头尾指针都指向自己就实现了初始化
 */
LTNode* ListInit(void)
{
    LTNode* phead = BuyListNode(-1);
    phead->next = phead;
    phead->prev = phead;
    retuen perror;
}

/* 打印双向链表 */
void ListPrint(LTNode* phead)
{
    assert(phead);/* 断言函数 */
    LTNode* cur = phead->next;
    while(cur != phead)
    {
        printf("%d ", cur->data);
        cur = cur->next;
    }
}

/* 双向链表尾插 */
void ListPushBack(LTNode* phead, LTDateType x)
{
    assert(phead);
    LTNode* new_node = BuyListNode(x);
    LTNode* tail = phead->prev;
    tail->next = new_node;
    new_node->prev = tail;
    new_node->next = phead;
    phead->prev = new_node;
}

/* 双向链表尾删 */
void ListPopBack(LTNode *phead)
{
    assert(phead);
    LTNode* tail = phead->prev;
    LTNode* tailprev = tail->prev;
    tailprev->next = phead;
    phead->prev = tailprev;
}
/* 双向链表头插法 */

void ListPushFront(LTNode* phead, LTDateType x)
{
    assert(phead);
    LTNode* new_node = BuyListNode(x);
    LTNode* first = phead->next;
    phead->next = new_node;
    new_node->prev = phead;
    new_node->next = first;
	first->prev = newnode;
}
/* 双向链表头删法 */
void ListPopFront(LTNode* phead)
{
	assert(phead);
	assert(phead->next != phead);//是否为空
	LTNode* first = phead->next;
	LTNode* second = first->next;
	free(first);
	phead->next = second;
	second->prev = phead;
}

/* 双向链表查找 */
LTNode* ListFind(LTNode* phead, LTDataType x)
{
	assert(phead);
	LTNode* cur = phead->next;
	while (cur != phead)
	{
		if (cur->data == x)
		{
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}

/* 双向链表再POS前面插入 */
void ListInsert(LTNode* pos, LTDataType x)
{
	assert(pos);
	LTNode* prev = pos->prev;
	LTNode* newnode = BuyListNode(x);
	//prev  newnode  pos
	prev->next = newnode;
	newnode->prev = prev;
	newnode->next = pos;
	pos->prev = newnode;
}

/* 双向链表删除pos位置的节点 */
void ListErase(LTNode* pos)
{
	assert(pos);
	LTNode* prev = pos->prev;
	LTNode* next = pos->next;
	free(pos);
	prev->next = next;
	next->prev = prev;
}
/* 摧毁链表 */
void ListDestory(LTNode* phead)
{
	assert(phead);
	LTNode* cur = phead->next;
	while (cur != phead)
	{
		LTNode* next = cur->next;
		free(cur);
		cur = next;
	}
	free(phead);
}

/* 双向链表的长度 */
size_t ListSize(LTNode* phead)
{
	assert(phead);
	size_t size = 0;
	LTNode* cur = phead->next;
	while (cur != phead)
	{
		++size;
		cur = cur->next;
	}
	return size;
}
/* 判断链表是否为空 */
bool ListEmpty(LTNode* phead)
{
	assert(phead);
	return phead->next == phead;
}