#include <stdio.h>
#include <stdlib.h>

#include "base.h"
#include "mem_pool.h"

static u32 magic_id[2]={0x12345678,0x87654321};

static void list_init(LIST_NODE *node)
{
	node->prev = node->next = node;
}

static void list_head_init(LIST_HEAD *head)
{
	list_init(&head->node);
	head->count = 0;
}

static void list_insert(LIST_NODE *prev, LIST_NODE *node)
{
	node->next = prev->next;
	node->prev = prev;
	prev->next->prev = node;
	prev->next = node;
}
static void list_remove(LIST_HEAD *head, LIST_NODE *node)
{
	LIST_NODE *prev = node->prev, *next = node->next;
	prev->next = next;
	next->prev = prev;
	list_init(node);
	head->count--;
}
static void list_insertTail(LIST_HEAD *head, LIST_NODE *node)
{
	list_insert(head->node.prev, node);
	head->count++;
}
static void list_insertHead(LIST_HEAD *head, LIST_NODE *node)
{
	list_insert(&head->node, node);
	head->count++;
}

static int list_free_count(LIST_HEAD *head)
{
	return head->count;
}
static LIST_NODE *list_get(LIST_HEAD *head)
{
	LIST_NODE *node = head->node.next;
	if(head->count == 0)
		return NULL;
	list_remove(head, node);
	return node;
}

static void *static_malloc(MEM_POOL *ppool)
{
	LIST_NODE *node;
	if((node = list_get(&ppool->list_head)) == NULL)
		return NULL;

	return node+1;
}

static void static_free(MEM_POOL *ppool, void *p)
{
	LIST_NODE *node = (LIST_NODE *)p;
	node--;
	if(node->next != node && node->prev != node) /* 正在使用的节点已经从链表中摘除, 该结点的链域指向自己 */
	{
		printf("%s static free assert fail\n", ppool->name);
		return ;
	}
	list_insertTail(&ppool->list_head, node);
}

/* 
 * size: 分配的块大小?? 
 * count: 可以分配的块数目
 */
int mem_pool_init(MEM_POOL *ppool, int size, int count,
				  char *p_static_buf, int static_buf_size, const char *name)
{
	int i;
	LIST_NODE *node;

	memset(ppool, 0, sizeof(MEM_POOL));
	ppool->name = name;
	ppool->size = size;
	list_head_init(&ppool->list_head);

	ppool->get = static_malloc;
	ppool->put = static_free;

	ppool->p_static_buf = p_static_buf;
	p_static_buf = (char *)MEM_ALIGN(p_static_buf);
	printf("size = %d, MEM_NODE_SIZE(size) = %d\n", size, MEM_NODE_SIZE(size));
	for(i = 0; i < count; i++)
	{
		node = (LIST_NODE *)p_static_buf;
		list_insertTail(&ppool->list_head, node);
		p_static_buf += MEM_NODE_SIZE(size);
		if(p_static_buf > ppool->p_static_buf + static_buf_size)
		{
			printf("%s mem pool is bad", name);
			return ;
		}
	}
	return 0;
}

void *mem_malloc(MEM_POOL *ppool)
{
	u32 *mg;
	void *p = ppool->get(ppool);
	if(p == NULL)
	{
		printf("Fail to malloc mem for %s\r\n", ppool->name);
		return NULL;
	}
	ppool->malloc_count++;
	ppool->used++;
	if(ppool->used > ppool->max_used)
		ppool->max_used = ppool->used;
	memset(p, 0, ppool->size);
	mg = (u32 *)(((u8 *)p) + ppool->size);
	memcpy(mg, &magic_id, sizeof(magic_id));

	return p;
}

void mem_free(MEM_POOL *ppool, void *p)
{
	u32 *mg;

	ppool->put(ppool, p);
	ppool->free_count++;
	ppool->used--;
	mg = (u32 *)(((u8 *)p) + ppool->size);
	if(memcmp(mg, &magic_id, sizeof(magic_id)) != 0)
	{
		printf("mem operate err in %s\r\n", ppool->name);
	}
}
