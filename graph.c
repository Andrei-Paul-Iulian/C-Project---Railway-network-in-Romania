#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "queue.h"

#define initial 1
#define waiting 2
#define visited 3

int **matrice1, **matrice2;
int *stare,*reach;

typedef struct graph_t 
{
  list_t *nodes;
  int **matrix;
  
  unsigned int num_nodes;
  unsigned int num_edges;
  
} graph_t;

graph_t *graph_create()
{
  graph_t *graph = NULL;

  graph=(graph_t*)malloc(sizeof(graph_t));

  graph->num_nodes=0;
  graph->num_edges=0;

  return graph;
}

void graph_print_neorientat(graph_t *graph)
{
  int i, j;

  for (i = 0 ; i < graph->num_nodes ; i++) 
  {
    for (j = 0; j < graph->num_nodes ; j++)
      printf("%d ", matrice1[i][j]);

    printf("\n");
  }

}

void graph_print_orientat(graph_t *graph)
{
  int i, j;

  for (i = 0 ; i < graph->num_nodes ; i++) 
  {
    for (j = 0; j < graph->num_nodes ; j++)
      printf("%d ", matrice2[i][j]);

    printf("\n");
  }

}


void test(FILE *f)
{
    if(f==NULL)
    {
        printf("Fisierul nu a putut fi deschis");
        exit(1);
    }
}

void file_read(list_t *list) 
{
    FILE *f,*g;
    list_t *listcopy;
    int i=0,aux,j;
    char *numefisier,*nume_oras;
    
    numefisier=(char*)malloc(10*sizeof(char));
    nume_oras=(char*)malloc(40*sizeof(char));

    f=fopen("_all_files.txt", "r");
    test(f);

    while(fscanf(f, "%s", numefisier)==1)
    {
        g=fopen(numefisier, "r");
        test(g);

        while(fgets(nume_oras, 40, g))
        {       
            listcopy=list;         

            if(list_search(listcopy, nume_oras)==0)
            {   
                listcopy=list;     
                list_add(listcopy, i, nume_oras);
                i++;
            }
        }
        fclose(g);
    }
    fclose(f);

}

void create_graph(graph_t *graph, int x) 
{
    FILE *f,*g;
    int i=0,aux,j;
    char *numefisier,*nume_oras1, *nume_oras2;
    
    numefisier=(char*)malloc(10*sizeof(char));
    nume_oras1=(char*)malloc(40*sizeof(char));
    nume_oras2=(char*)malloc(40*sizeof(char));

    f=fopen("_all_files.txt", "r");
    test(f);

    while(!feof(f))
    {
        fscanf(f, "%s", numefisier);

        g=fopen(numefisier, "r");
        test(g);
        
        fgets(nume_oras1, 40, g);
        while(!feof(g))
        {
          fgets(nume_oras2, 40, g);

          i=node_number(graph->nodes, nume_oras1);
          j=node_number(graph->nodes, nume_oras2);
          
          if(i!=j && x==0)
          {
            matrice1[i][j]=1;
            matrice1[j][i]=1;
          }
          if(i!=j && x==1)
          {
            matrice2[i][j]=1;
          }  

          strcpy(nume_oras1,nume_oras2);          
        }
        fclose(g);
    }  
    fclose(f);
                     
}

int prima_statie(int n)
{
  int i,j,suma=0,max=0,aux;

  for(i=0;i<n;i++)
  {
    suma=0;
    for(j=0;j<n;j++)
    {
      suma=suma+matrice1[i][j];
    }
    if(suma > max)
    {
      max=suma;
      aux=i;
    }
  }

  return aux;
}

int statia_doi(int n, int nr)
{
  int i,j,suma=0,max=0,aux;

  for(i=0;i<n;i++)
  {
    suma=0;
    for(j=0;j<n;j++)
    {
      suma=suma+matrice1[i][j];
    }
    if(suma > max && i!=nr)
    {
      max=suma;
      aux=i;
    }
  }

  return aux;
}

int cautare_statia_mea(int n, int nr)
{
  int i,suma=0;
  
  for(i=0;i<n;i++)
  {
    suma=suma+matrice1[nr][i];
  }
  
  if(suma==0)
  return -1;
  else
  return suma;
}

void BFS(list_t *list, int v, int n)
{
	int i;
  char y[40];
  queue_t* queue;
  FILE *h;

  queue_create();
	
	queue_push(queue, v);

  h=fopen("parcurgere_bfs.txt", "w+");
  test(h);

	stare[v] = waiting;

	while(queue_empty(queue)!=0)
	{
		v = queue_pop(queue);

    strcpy(y,node_name(list, v));
    
    fprintf(h,"%s", y);

		stare[v] = visited;
		
		for(i=0; i<n; i++)
		{
			if(matrice1[v][i] == 1 && stare[i] == initial) 
			{
				queue_push(queue, i);
				stare[i] = waiting;
			}
		}
	}
  fclose(h);

	printf("\n");
}

void DFS(list_t *list, int i, int n)
{
  int j;
  char y[30];
  FILE *f;
  
  strcpy(y,node_name(list, i));

  f=fopen("parcurgere_dfs.txt", "a");
  test(f);
	fprintf(f,"%s", y);
  fclose(f);

  reach[i]=1;
	
	for(j=0;j<n;j++)
    if(!reach[j] && matrice1[i][j]==1)
      DFS(list, j, n);
}

int main()
{
    graph_t *graph, *graphcopy;
    list_t *list,*listcopy;
    int n,i,j,x,aux;
    FILE *f;
    char v[30];

    graph=graph_create();
    list=list_create();
    graph->nodes=list;
    
    listcopy=list;
    file_read(listcopy);
    
    listcopy=list;
    list_print(listcopy);

    printf("Numarul de noduri este %d\n\n", list->length);

    n=list->length;

    f=fopen("noduri.txt", "w");
    test(f);
    fprintf(f, "%d", n);
    fclose(f);

//Alocarea dinamica pentru prima matrice

    matrice1=(int**)malloc(n*sizeof(int*));
    if(matrice1==NULL)
    {
      printf("Alocare dinamica esuata");
    }

    for(i=0;i<n;i++)
    {
      (matrice1)[i]=(int*)calloc(n, sizeof(int));
      if(matrice1[i]==NULL)
      {
        printf("Alocare dinamica esuata %d\n", i);
      }
    }
//Alocarea dinamica pentru a doua matrice

    matrice2=(int**)malloc(n*sizeof(int*));
    if(matrice2==NULL)
    {
      printf("Alocare dinamica esuata");
    }

    for(i=0;i<n;i++)
    {
      (matrice2)[i]=(int*)calloc(n, sizeof(int));
      if(matrice2[i]==NULL)
      {
        printf("Alocare dinamica esuata %d\n\n", i);
      }
    }

//Aici creez graful neorientat 

    graphcopy=graph;
    create_graph(graphcopy,0);
    
    aux=0;
    for (i = 0 ; i < n ; i++) 
    {
        for (j = 0; j < n ; j++)
        if(matrice1[i][j]==1)
        aux++;
    }
    printf("Numarul de muchii de pe graful neorientat este %d\n\n", aux/2);

    f=fopen("muchii.txt", "w");
    test(f);
    fprintf(f, "%d - graf neorientat\n", aux/2);
    fclose(f);

//Aici creez graful orientat

    graphcopy=graph;
    create_graph(graphcopy,1);
    
    aux=0;
    for (i = 0 ; i < n ; i++) 
    {
        for (j = 0; j < n ; j++)
        if(matrice2[i][j]==1)
        aux++;
    }
    printf("Numarul de muchii de pe graful orientat este %d\n\n", aux);

    f=fopen("muchii.txt", "a");
    test(f);
    fprintf(f, "%d - graf orientat\n", aux);
    fclose(f);
    
    aux=prima_statie(n);

    strcpy(v,node_name(list, aux));

    printf("Cea mai vizitata statie este %s\n", v);

    f=fopen("primul.txt", "w");
    test(f);
    fprintf(f, "%s", v);
    fclose(f);

    i=statia_doi(n,aux);

    strcpy(v,node_name(list, i));

    printf("A doua cea mai vizitata statie este %s\n", v);

    f=fopen("doilea.txt", "w");
    test(f);
    fprintf(f, "%s", v);
    fclose(f);

    char y[30]="Tulcea Oras";
 
    y[strlen(y)] = '\n';
    y[strlen(y)] = '\0';

    i=node_number(list,y);
    j=cautare_statia_mea(n,i);
    
    printf("Orasul meu este %s\n", y);
    printf("Gradul statiei din orasul meu este %d\n\n", j);

    f=fopen("orasul_meu.txt", "w");
    test(f);
    fprintf(f, "%d", j);
    fclose(f);

//BFS

    stare=(int*)malloc(n*sizeof(int));
    
    int val;

    for(val=0; val<n; val++) 
		stare[val] = initial;
    
    BFS(list, 0, n);

//DFS
    reach=(int*)malloc(n*sizeof(int));
    
    for(val=0; val<n; val++) 
		reach[val] = 0;
    
    f=fopen("parcurgere_dfs.txt", "w");
    test(f); 
    fclose(f);

    DFS(list, 0, n); 

//Dezalocare memorie

    for(i=0;i<n;i++)
    {
      free(matrice1[i]);
      free(matrice2[i]);
    }
    free(matrice1);
    free(matrice2);

    free(stare);
    free(reach);   
    
}   
