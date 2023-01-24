#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "queue.h"

queue_t *queue_create()
{
	queue_t *queue;

	queue = (queue_t*)malloc(sizeof(queue_t));
	queue->head = NULL;
	queue->tail = NULL;
	queue->length = 0;

	return queue;
}

queue_node_t *queue_node_create(int val)
{
	queue_node_t *node = NULL;

	node = (queue_node_t*)malloc(sizeof(queue_node_t));
	node->val=val;

	node->next = NULL;

	return node;
}

void queue_push(queue_t *queue, int val)
{
	queue_node_t *node = NULL;

	node=queue_node_create(val);

	if(queue->length>=1)
	{
		queue->tail->next=node;
		queue->tail=node;
	}
	else
	{
		queue->head=node;
		queue->tail=node;

	}

	queue->length++;

}

int queue_pop(queue_t *queue)
{
	int val=0;
	queue_node_t *node;

	val=queue->head->val;

    node=queue->head;
	queue->head=queue->head->next;
    
	node=NULL;

	queue->length--;

	return val;
}

int queue_front(queue_t *queue)
{
	if(queue == NULL || queue->head == NULL)
		return 0;

	return queue->head->val;
}

int queue_back(queue_t *queue)
{
	if(queue == NULL || queue->tail == NULL)
		return 0;

	return queue->tail->val;
}

int queue_empty(queue_t *queue)
{
	return queue->length;
}

int queue_length(queue_t *queue)
{
	return queue->length;
}

int queue_search(queue_t *queue, char *nume_oras)
{
	while(queue->head!=NULL)
	{
		if(strcmp(nume_oras,queue->head->nume_oras)==0)
		{
			return 1;
		}
        else
		queue->head = queue->head->next;
	}
	return 0;
}

void queue_print(queue_t *queue)
{
	queue_node_t *node;

	node = queue->head;

	while(node!=NULL) 
	{
		printf("%d \n", node->val);
		node = node->next;
	}
}