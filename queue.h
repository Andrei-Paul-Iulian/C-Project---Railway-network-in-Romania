#ifndef QUEUE_H_
#define QUEUE_H

#include <stdio.h>

typedef struct queue_node_t 
{
	int val;
	char nume_oras[25];

	struct queue_node_t *next;

} queue_node_t;

typedef struct queue_t {

	struct queue_node_t *head;

	struct queue_node_t *tail;

	unsigned int length;
} queue_t;

queue_t *queue_create();

queue_node_t *queue_node_create(int val);

void queue_push(queue_t *queue, int val);

int queue_pop(queue_t *queue);

int queue_front(queue_t *queue);

int queue_back(queue_t *queue);

int queue_empty(queue_t *queue);

int queue_length(queue_t *queue);

void queue_print(queue_t *queue);

int queue_search(queue_t *queue, char *nume_oras);

#endif