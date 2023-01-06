#define LTDateType uint8_t

/* �������� */
typedef struct ListNode
{
    struct ListNode* next;
    struct ListNode* prev;
    LTDateType data;
}LTNode;


/* ����һ����̬ͷ�ڵ� */
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

/* ��ʼ������ 
 * �������ͷβָ�붼ָ���Լ���ʵ���˳�ʼ��
 */
LTNode* ListInit(void)
{
    LTNode* phead = BuyListNode(-1);
    phead->next = phead;
    phead->prev = phead;
    retuen perror;
}

/* ��ӡ˫������ */
void ListPrint(LTNode* phead)
{
    assert(phead);/* ���Ժ��� */
    LTNode* cur = phead->next;
    while(cur != phead)
    {
        printf("%d ", cur->data);
        cur = cur->next;
    }
}

/* ˫������β�� */
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

/* ˫������βɾ */
void ListPopBack(LTNode *phead)
{
    assert(phead);
    LTNode* tail = phead->prev;
    LTNode* tailprev = tail->prev;
    tailprev->next = phead;
    phead->prev = tailprev;
}
/* ˫������ͷ�巨 */

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
/* ˫������ͷɾ�� */
void ListPopFront(LTNode* phead)
{
	assert(phead);
	assert(phead->next != phead);//�Ƿ�Ϊ��
	LTNode* first = phead->next;
	LTNode* second = first->next;
	free(first);
	phead->next = second;
	second->prev = phead;
}

/* ˫��������� */
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

/* ˫��������POSǰ����� */
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

/* ˫������ɾ��posλ�õĽڵ� */
void ListErase(LTNode* pos)
{
	assert(pos);
	LTNode* prev = pos->prev;
	LTNode* next = pos->next;
	free(pos);
	prev->next = next;
	next->prev = prev;
}
/* �ݻ����� */
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

/* ˫������ĳ��� */
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
/* �ж������Ƿ�Ϊ�� */
bool ListEmpty(LTNode* phead)
{
	assert(phead);
	return phead->next == phead;
}