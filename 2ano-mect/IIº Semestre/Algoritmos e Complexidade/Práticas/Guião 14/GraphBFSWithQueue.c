//
// Joaquim Madeira, AlgC, May 2020
// João Manuel Rodrigues, AlgC, May 2020
//
// GraphBFS - QUEUE-based Breadth-First Search
//

/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Algoritmo e Complexidade | 2º Ano-2º semestre
 * Curso: MIECT  
 * Junho-Julho 2021
 */

#include "GraphBFSWithQueue.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "IntegersQueue.h"
#include "IntegersStack.h"

struct _GraphBFSWithQueue
{
  unsigned int *marked;
  int *distance;
  int *predecessor;
  Graph *graph;
  unsigned int startVertex;
};
//<--auxiliar functions
static void _bfsWithQueue(GraphBFSWithQueue* traversal, unsigned int vertex, unsigned int numVertices){
  Queue* queue = QueueCreate(numVertices);

  QueueEnqueue(queue, vertex); 
  traversal->marked[vertex] = 1;

  while(!QueueIsEmpty(queue)){

    vertex = QueueDequeue(queue);
    unsigned int* neighbors = GraphGetAdjacentsTo(traversal->graph, vertex); 

    for (int i = 1; i <= neighbors[0]; i++) {
      unsigned int w = neighbors[i];

      if(traversal->marked[w] == 0){
        traversal->predecessor[w] = vertex;
        traversal->distance[w]=traversal->distance[vertex]+1;
        QueueEnqueue(queue, w);
        traversal->marked[w] = 1;
      }
    } 
    free(neighbors);
  }
  QueueDestroy(&queue);
}
//-->
GraphBFSWithQueue *GraphBFSWithQueueExecute(Graph *g, unsigned int startVertex)
{
  assert(g != NULL);
  assert(0 <= startVertex && startVertex < GraphGetNumVertices(g));

  GraphBFSWithQueue *traversal = (GraphBFSWithQueue *)malloc(sizeof(struct _GraphBFSWithQueue));
  assert(traversal != NULL);

  unsigned int numVertices = GraphGetNumVertices(g);

  //
  // W !!
  //
  // CRIAR e INICIALIZAR os campos de traversal
  // traversal->marked
  // traversal->distance
  // traversal->predecessor
  //
    traversal->marked = (unsigned int *)calloc(numVertices, sizeof(unsigned int));
  assert(traversal->marked != NULL);
  traversal->predecessor = (int *)malloc(numVertices * sizeof(int));
  assert(traversal->predecessor != NULL);
  traversal->distance = (int *)malloc(numVertices * sizeof(int));
  assert(traversal->distance != NULL);

   for (int i = 0; i < numVertices; i++)
  {
    traversal->predecessor[i] = -1;
  }
  traversal->predecessor[startVertex] = -1;

  for (int i = 0; i < numVertices; i++)
  {
    traversal->distance[i] = 10000;// o maior inteiro representado
  }
  traversal->distance[startVertex] = 0;

  traversal->graph = g;
  traversal->startVertex = startVertex;

  // EFETUAR A TRAVESSIA

  //<--Solution -->call auxiliar function
  _bfsWithQueue(traversal, startVertex, numVertices);
  //-->

  return traversal;
}

void GraphBFSWithQueueDestroy(GraphBFSWithQueue **p)
{
  assert(*p != NULL);

  GraphBFSWithQueue *aux = *p;

  free(aux->marked);
  free(aux->predecessor);

  free(*p);
  *p = NULL;
}

// Getting the result

unsigned int GraphBFSWithQueueHasPathTo(const GraphBFSWithQueue *p,
                                        unsigned int v)
{
  assert(0 <= v && v < GraphGetNumVertices(p->graph));

  return p->marked[v];
}

Stack *GraphBFSWithQueuePathTo(const GraphBFSWithQueue *p, unsigned int v)
{
  assert(0 <= v && v < GraphGetNumVertices(p->graph));

  Stack *s = StackCreate(GraphGetNumVertices(p->graph));

  if (p->marked[v] == 0)
  {
    return s;
  }

  // Store the path
  for (unsigned int current = v; current != p->startVertex;
       current = p->predecessor[current])
  {
    StackPush(s, current);
  }

  StackPush(s, p->startVertex);

  return s;
}

// DISPLAYING on the console

void GraphBFSWithQueueShowPath(const GraphBFSWithQueue *p, unsigned int v)
{
  assert(0 <= v && v < GraphGetNumVertices(p->graph));

  Stack *s = GraphBFSWithQueuePathTo(p, v);

  while (StackIsEmpty(s) == 0)
  {
    printf("%d ", StackPop(s));
  }

  StackDestroy(&s);
}

void GraphBFSWithQueueDisplay(const GraphBFSWithQueue *p)
{
  //<--Solution
  GraphDisplay(p->graph);
  for (int i = 0; i < GraphGetNumVertices(p->graph); i++)
  {
    GraphBFSWithQueueShowPath(p, i);
  }
  //-->
}
