/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Algoritmo e Complexidade | 2º Ano-2º semestre
 * Curso: MIECT  
 * Junho 2021
 */

// Joaquim Madeira, AlgC, June 2021
// João Manuel Rodrigues, AlgC, June 2021
//
// TESTING the TAD MinHeap implementation
//

// This program lists the largest K values from a file of random integers.

//// PROCURE ... E COMPLETE ////

// Try the arguments below.

//ARGS 10 ordenados02500.txt
//ARGS 10 ordInversa02500.txt
//ARGS 10 aleatorios02500.txt
//ARGS 100 aleatorios40000.txt

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "MinHeap.h"

// THE ALGORITHM:
//
// Read the first K values into a MIN-heap.
//
// Then:
//
// 1. Get the next value from the file -> current.
// 2. If current is smaller or equal than the MIN element from the heap,
//    then discard it.
// 3. Otherwise, remove the MIN from the heap and insert the current value.
//
// The MIN-heap stores the K largest values read from file.
//
// List the K largest values by successively removing the MIN from the heap.
//

// STORING POINTERS TO INTEGERS

// The comparator for integer items

int comparator(const void *p1, const void *p2)
{
  int d = *(int *)p1 - *(int *)p2;
  return (d > 0) - (d < 0);
}

// The printer for integer items

void printer(void *p) { printf("%d ", *(int *)p); }

// MAIN

int main(int argc, char *argv[])
{
  if (argc < 3)
  {
    fprintf(stderr, "Usage: %s K FILE\n", argv[0]);
    exit(1);
  }

  // k -> number of largest values we are looking for
  int k = atoi(argv[1]);

  FILE *f = fopen(argv[2], "r");
  if (f == NULL)
  {
    perror(argv[2]);
    exit(2);
  }

  // Create heap
  MinHeap *h = MinHeapCreate(k, comparator, printer); // <--Solution
  if (h == NULL)
    abort();

  // Read the first K values into a MIN-heap
  //    Allocate memory space for an integer
  //    Read it from file
  //    Insert it in the heap

  // <--Solution
  for (int i = 0; i < k; i++)
  {
    //    Allocate memory space for an integer
    int *aux = (int *)malloc(sizeof(int));

    //    Read it from file
    fscanf(f, "%d", aux);

    //    Insert it in the heap
    MinHeapInsert(h, (void *)aux);
  }
  //MinHeapView(h);//see heap
  

  // Read and process each one of the remaining values
  while (!feof(f))
  {
    //allocate memory
    int *aux = (int *)malloc(sizeof(int)); // <--Solution

    //read
    fscanf(f, "%d", aux);
    

    int *min = (int *)MinHeapGetMin(h);

    if (*aux > *min)
    {
      MinHeapRemoveMin(h);
      free(min);
      MinHeapInsert(h, (void *)aux);
    }
    else
    {
      free(aux); //-->
    }
  }
    // The heap stores the largest k values
    // List them by removing each one from the heap

    while (!MinHeapIsEmpty(h)) // <--Solution
    {                                    
      int *aux = (int *)MinHeapGetMin(h); //descobrir o minimo
      MinHeapRemoveMin(h);
      printf("%d\n", *aux);
      free(aux); //free; -->
    }

    // House-keeping
    MinHeapDestroy(&h);
    fclose(f);
  
}
