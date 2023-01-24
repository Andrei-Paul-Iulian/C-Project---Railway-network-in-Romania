#ifndef LIST_H
#define LIST_H

typedef struct list_node_t 
{
	char nume_oras[40];
	int val;
	int contor;

	struct list_node_t *next;

} list_node_t;

typedef struct list_t 
{
	struct list_node_t *head;
	struct list_node_t *tail;
	
	unsigned int length;

} list_t;

list_t *list_create();

void list_add(list_t *list, int val, char *nume_oras);

void list_print(list_t *list);

void list_remove(list_t *list, int val);

int list_search(list_t *list, char *nume_oras);

list_node_t *list_node_create(int val, char *nume_oras);

int node_number(list_t *list, char *nume);

char *node_name(list_t *list, int val);

int cautare(list_t *list, char *nume);

void contorizare(list_t *list, char *nume);

#endif