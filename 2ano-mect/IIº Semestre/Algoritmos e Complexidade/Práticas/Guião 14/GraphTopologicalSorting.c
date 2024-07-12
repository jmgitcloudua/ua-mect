//
// Joaquim Madeira, AlgC, June 2021
// João Manuel Rodrigues, AlgC, June 2021
//
// Topological Sorting
//

/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Algoritmo e Complexidade | 2º Ano-2º semestre
 * Curso: MIECT  
 * Junho-Julho 2021
 */

#include "GraphTopologicalSorting.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "IntegersQueue.h"

struct _GraphTopoSort
{
  unsigned int *marked;           // Aux array
  unsigned int *numIncomingEdges; // Aux array
  unsigned int *vertexSequence;   // The result
  unsigned int validResult;       // 0 or 1
  unsigned int numVertices;       // From the graph
  Graph *graph;
};

// AUXILIARY FUNCTION
// Allocate memory for the struct
// And for its array fields
// Initialize all struct fields
//
static GraphTopoSort *_create(Graph *g)
{
  //<--Solution
  GraphTopoSort *p = NULL;
  if (g == NULL)
  {
    abort();
  }

  p = (GraphTopoSort *)malloc(sizeof(struct _GraphTopoSort));
  p->marked = (unsigned int *)calloc(GraphGetNumVertices(g), sizeof(unsigned int));
  p->numIncomingEdges = (unsigned int *)calloc(GraphGetNumEdges(g), sizeof(unsigned int));

  for (int i = 0; i < GraphGetNumVertices(g); i++)
  {
    p->numIncomingEdges[i] = GraphGetVertexInDegree(g, i);
  }
  p->graph = g;
  p->numVertices = GraphGetNumVertices(g);
  p->vertexSequence = (unsigned int *)calloc(GraphGetNumVertices(g), sizeof(unsigned int));
  p->validResult = 0;

  return p;
  //-->
}

//
// Computing the topological sorting, if any, using the 1st algorithm:
// 1 - Create a copy of the graph
// 2 - Successively identify vertices without incoming edges and remove their
//     outgoing edges
// Check if a valid sorting was computed and set the isValid field
// For instance, by checking if the number of elements in the vertexSequence is
// the number of graph vertices
//
GraphTopoSort *GraphTopoSortComputeV1(Graph *g)
{
  assert(g != NULL && GraphIsDigraph(g) == 1);

  // Create and initialize the struct

  GraphTopoSort *topoSort = _create(g);

  // Build the topological sorting

  // COMPLETAR
  Graph *copy = GraphCopy(g);
  int count = 0;
  int found = 1;
  while (found)
  {
    found = 0;
    for (int i = 0; i < GraphGetNumVertices(copy); i++)
    {
      if (GraphGetVertexInDegree(copy, i) == 0 && topoSort->marked[i] == 0)
      {
        topoSort->marked[i] = 1;
        found = 1;
        topoSort->vertexSequence[count++] = i;

        unsigned int *arrCopy = GraphGetAdjacentsTo(copy, i);

        for (int j = 1; j <= arrCopy[0]; j++)
        {
          GraphRemoveEdge(copy, i, arrCopy[j]);
        }

        free(arrCopy);
        break;
      }
    }
  }

  if (GraphGetNumVertices(copy) == count)
  {
    topoSort->validResult = 1;
  }

  GraphDestroy(&copy);

  return topoSort;
}

//
// Computing the topological sorting, if any, using the 2nd algorithm
// Check if a valid sorting was computed and set the isValid field
// For instance, by checking if the number of elements in the vertexSequence is
// the number of graph vertices
//
GraphTopoSort *GraphTopoSortComputeV2(Graph *g)
{
  assert(g != NULL && GraphIsDigraph(g) == 1);

  // Create and initialize the struct

  GraphTopoSort *topoSort = _create(g);

  // Build the topological sorting

  //<--Solution

  int found = 1;
  int count = 0;
  while (found)
  {
    found = 0;
    for (int i = 0; i < GraphGetNumVertices(g); i++)
    {
      if (topoSort->marked[i] == 0 && topoSort->numIncomingEdges[i] == 0)
      {
        topoSort->marked[i] = 1;
        found = 1;
        topoSort->vertexSequence[count++] = i;

        unsigned int *arrAux = GraphGetAdjacentsTo(g, i);

        for (int j = 1; j <= arrAux[0]; j++)
        {
          topoSort->numIncomingEdges[arrAux[j]]--;
        }
        free(arrAux);
        break;
      }
    }
  }
  if (GraphGetNumVertices(g) == count)
  {
    topoSort->validResult = 1;
  }

  return topoSort;
  //-->
}

//
// Computing the topological sorting, if any, using the 3rd algorithm
// Check if a valid sorting was computed and set the isValid field
// For instance, by checking if the number of elements in the vertexSequence is
// the number of graph vertices
//
GraphTopoSort *GraphTopoSortComputeV3(Graph *g)
{
  assert(g != NULL && GraphIsDigraph(g) == 1);

  // Create and initialize the struct

  GraphTopoSort *topoSort = _create(g);

  // Build the topological sorting

  //<--Solution

  Queue *q = QueueCreate(topoSort->numVertices);
  int i;
  for (i = 0; i < GraphGetNumVertices(g); i++)
  {
    if (topoSort->marked[i] == 0 && topoSort->numIncomingEdges[i] == 0)
    {
      topoSort->marked[i] = 1;
      QueueEnqueue(q, i);
    }
  }
  int count = 0;
  while (!QueueIsEmpty(q))
  {
    int v = QueueDequeue(q);
   
    topoSort->vertexSequence[count++] = v;
   
    unsigned int *arrAux = GraphGetAdjacentsTo(g, v);
    for (int j = 1; j <= arrAux[0]; j++)
    {

      topoSort->numIncomingEdges[arrAux[j]]--;
      if (topoSort->marked[arrAux[j]] == 0 && topoSort->numIncomingEdges[arrAux[j]] == 0)
      {
       
        topoSort->marked[arrAux[j]] = 1;
        QueueEnqueue(q, arrAux[j]);
      }
      
    }
    free(arrAux);
  }
  if (GraphGetNumVertices(g) == count)
  {
    topoSort->validResult = 1;
  }
  QueueDestroy(&q);

  return topoSort;
  //-->
}

void GraphTopoSortDestroy(GraphTopoSort **p)
{
  assert(*p != NULL);

  GraphTopoSort *aux = *p;

  free(aux->marked);
  free(aux->numIncomingEdges);
  free(aux->vertexSequence);

  free(*p);
  *p = NULL;
}

//
// A valid sorting was computed?
//
int GraphTopoSortIsValid(const GraphTopoSort *p) { return p->validResult; }

//
// Getting an array containing the topological sequence of vertex indices
// Or NULL, if no sequence could be computed
// MEMORY IS ALLOCATED FOR THE RESULTING ARRAY
//
unsigned int *GraphTopoSortGetSequence(const GraphTopoSort *p)
{
  // COMPLETAR
  // ...
  return NULL;
}

// DISPLAYING on the console

//
// The toplogical sequence of vertex indices, if it could be computed
//
void GraphTopoSortDisplaySequence(const GraphTopoSort *p)
{
  if (p->validResult == 0)
  {
    printf(" *** The topological sorting could not be computed!! *** \n");
    return;
  }

  printf("Topological Sorting - Vertex indices:\n");
  for (int i = 0; i < GraphGetNumVertices(p->graph); i++)
  {
    printf("%d ", p->vertexSequence[i]);
  }
  printf("\n");
}

//
// The toplogical sequence of vertex indices, if it could be computed
// Followed by the digraph displayed using the adjecency lists
// Adjacency lists are presented in topologic sorted order
//
void GraphTopoSortDisplay(const GraphTopoSort *p)
{
  // The topological order
  GraphTopoSortDisplaySequence(p);

  if (p->validResult == 0)
  {
    return;
  }

  // The Digraph
  for (int i = 0; i < GraphGetNumVertices(p->graph); i++)
  {
    GraphListAdjacents(p->graph, p->vertexSequence[i]);
  }
  printf("\n");
}
