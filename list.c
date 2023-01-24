#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

list_t *list_create()
{
	list_t *list;

	list = (list_t*)malloc(sizeof(list_t));

	list->head = NULL;
	list->tail = NULL;
	list->length = 0;

	return list;
}

list_node_t *list_node_create(int val, char *nume_oras)
{
	list_node_t *node; 

	node=(list_node_t*)malloc(sizeof(list_node_t));

	node->val = val;

	strcpy(node->nume_oras, nume_oras);

    node->contor = 1;

	node->next = NULL;

	return node;
}

void list_add(list_t *list, int val, char *nume_oras)
{
	list_node_t *node; 
	node = list_node_create(val, nume_oras);
	if(list->head==NULL) 
	{
		list->head = node;
		list->tail = node;
		list->length++;
		return;
	}

	list->tail->next = node;
	list->tail = list->tail->next;
	list->length++;

}

int list_search(list_t *list, char *nume_oras)
{
	int aux=0;

    list_node_t *node;

	node=list->head;
	
	while(node!=NULL)
	{
		if(strcmp(nume_oras,node->nume_oras)==0)
		{
			contorizare(list, nume_oras); 
			aux=1;
		}
		node = node->next;
	}
	return aux;
}

int node_number(list_t *list, char *nume)
{
	int aux=-1;

    list_node_t *node;

	node=list->head; 
	
	while(node!=NULL)
	{
		if(strcmp(nume,node->nume_oras)==0)
		{
			aux=node->val;
		}
		node = node->next;
	}
	return aux;
}

char *node_name(list_t *list, int val)
{
	char *v;

	v=(char*)malloc(30*sizeof(char));

    list_node_t *node;

	node=list->head; 
	
	while(node!=NULL)
	{
		if(node->val==val)
		{
			strcpy(v,node->nume_oras);
		}
		node = node->next;
	}
	return v;
}

void list_print(list_t *list)
{
	list_node_t *node;

	node = list->head;

	while(node!=NULL) 
	{
		printf("%d %s", node->val, node->nume_oras);
		node = node->next;
	}
}

int cautare(list_t *list, char *nume)
{
	int aux=-1;
    list_node_t *node;

	node=list->head; 
	
	while(node!=NULL)
	{
		if(strcmp(nume,node->nume_oras)==0)
		{
			aux=node->contor;
		}
		node = node->next;
	}
	return aux;
}

void contorizare(list_t *list, char *nume)
{
    list_node_t *node;

	node=list->head; 
	
	while(node!=NULL)
	{
		if(strcmp(nume,node->nume_oras)==0)
		{
			node->contor = node->contor + 1;
		}
		node = node->next;
	}
}

