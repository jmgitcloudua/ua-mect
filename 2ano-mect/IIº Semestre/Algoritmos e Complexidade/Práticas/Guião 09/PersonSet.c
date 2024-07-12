/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Algoritmo e Complexidade | 2º Ano-2º semestre
 * Curso: MIECT  
 * Maio 2021
 */

// Complete the functions (marked by ...)
// so that it passes all tests in DateTimeTest.

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "PersonSet.h"

// Definition of the structure
struct _PersonSet_
{
  int capacity;   // the current capacity of the array
  int size;       // the number of elements currently stored
  Person **array; // points to an array of pointers to persons
};

#define INITIAL_CAPACITY 4

// You may add auxiliary definitions and declarations here, if you need to.

// Create a PersonSet.
PersonSet *PersonSetCreate()
{
  // You must allocate space for the struct and for the array.
  // The array should be created with INITIAL_CAPACITY elements.
  // (The array will be reallocated if necessary, when elements are appended.)

  //Solution
  PersonSet *ps = (PersonSet *)malloc(sizeof(*ps));
  if (ps == NULL)
  {
    return NULL;
  }
  ps->array = (Person **)malloc(INITIAL_CAPACITY * sizeof(Person *));
  if (ps->array == NULL)
  {
    free(ps);
    return NULL;
  }
  ps->capacity = INITIAL_CAPACITY;
  ps->size = 0;

  return ps;
}

// Destroy PersonSet *pps
void PersonSetDestroy(PersonSet **pps)
{
  assert(*pps != NULL);

  //Solution
  free((*pps)->array);
  free(*pps);
  *pps = NULL;
}

int PersonSetSize(const PersonSet *ps)
{
  return ps->size;
}

int PersonSetIsEmpty(const PersonSet *ps)
{
  return ps->size == 0;
}

void PersonSetPrint(const PersonSet *ps)
{
  printf("{\n");
  for (int i = 0; i < ps->size; i++)
  {
    Person *p = ps->array[i];
    PersonPrintf(p, ";\n");
  }
  printf("}(size = %d, capacity = %d)\n", ps->size, ps->capacity);
}

// Find index in ps->array of person with given id.
// (INTERNAL function.)
static int search(const PersonSet *ps, int id)
{
  //Solution
  for (int i = 0; i < ps->size; i++)
  {
    if (ps->array[i]->id == id)
    {
      return i;
    }
  }
  return -1; // if not found
}

// Append person *p to *ps, without verifying presence.
// Use only when sure that *p is not contained in *ps!
// (INTERNAL function.)
static void append(PersonSet *ps, Person *p)
{
  // MODIFY the function so that if the array is full,
  // use realloc to double the array capacity!

  //Solution
  if (ps->size == ps->capacity) //check if the array is full
  {
    ps->capacity *= 2;
    ps->array = realloc(ps->array, ps->capacity * sizeof(Person *));
    assert(ps->array != NULL);
  }
  ps->array[ps->size] = p;
  ps->size++;
}

// Add person *p to *ps.
// Do nothing if *ps already contains a person with the same id.
void PersonSetAdd(PersonSet *ps, Person *p)
{
  // You may call the append function here!

  //Solution
  if (search(ps, p->id) == -1)
  {
    append(ps, p);
  }
}

// Pop one person out of *ps.
Person *PersonSetPop(PersonSet *ps)
{
  assert(!PersonSetIsEmpty(ps));
  // It is easiest to pop and return the person in the last position!

  //Solution
  Person *p = ps->array[ps->size - 1]; // set last position
  ps->array[ps->size - 1] = NULL;
  ps->size--;

  return p;
}

// Remove the person with given id from *ps, and return it.
// If no such person is found, return NULL and leave set untouched.
Person *PersonSetRemove(PersonSet *ps, int id)
{
  // You may call search here!

  //Solution
  Person *p;
  int i = search(ps, id);
  if (i == -1) // if not found
  {
    return NULL;
  }
  p = ps->array[i];
  ps->array[i] = ps->array[ps->size - 1];
  ps->array[ps->size - 1] = NULL; // just for defensive programing, but not needed
  ps->size--;

  return p;
}

// Get the person with given id of *ps.
// return NULL if it is not in the set.
Person *PersonSetGet(const PersonSet *ps, int id)
{
  // You may call search here!

  //Solution
  int i = search(ps, id);
  if (i == -1)
  {
    return NULL;
  }
  return ps->array[i];
}

// Return true (!= 0) if set contains person wiht given id, false otherwise.
int PersonSetContains(const PersonSet *ps, int id)
{
  return search(ps, id) >= 0;
}

// Return a NEW PersonSet with the union of *ps1 and *ps2.
// Return NULL if allocation fails.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetUnion(const PersonSet *ps1, const PersonSet *ps2)
{
  PersonSet *ps = PersonSetCreate();

  //Solution
  for (int i = 0; i < ps1->size; i++)
  {
    append(ps, ps1->array[i]);
  }
  for (int j = 0; j < ps2->size; j++)
  {
    PersonSetAdd(ps, ps2->array[j]);
  }

  return ps;
}

// Return a NEW PersonSet with the intersection of *ps1 and *ps2.
// Return NULL if allocation fails.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetIntersection(const PersonSet *ps1, const PersonSet *ps2)
{
  //Solution
  PersonSet *ps = PersonSetCreate();

  if (ps == NULL)
  {
    return NULL;
  }

  for (int i = 0; i < ps1->size; i++)
  {
    for (int j = 0; j < ps2->size; j++)
    {
      if (ps1->array[i]->id == ps2->array[j]->id)
      {
        append(ps, ps1->array[i]);
      }
    }
  }

  return ps;
}

// Return a NEW PersonSet with the set difference of *ps1 and *ps2.
// Return NULL if allocation fails.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetDifference(const PersonSet *ps1, const PersonSet *ps2)
{
  //Solution
  PersonSet *ps = PersonSetCreate();

  for (int i = 0; i < ps1->size; i++)
  {
    if (search(ps2, ps1->array[i]->id) == -1)
    {
      append(ps, ps1->array[i]);
    }
  }
  return ps;
}

// Return true iff *ps1 is a subset of *ps2.
int PersonSetIsSubset(const PersonSet *ps1, const PersonSet *ps2)
{
  //Solution
  int i, j;
  for (i = 0; i < ps1->size; i++)
  {
    for (j = 0; j < ps2->size; j++)
    {
      if (ps1->array[i]->id == ps2->array[j]->id)
      {
        break;
      }
    }
  }
  if (j == ps2->size)
  {
    return 0;
  }

  return 1;
}

// Return true if the two sets contain exactly the same elements.
int PersonSetEquals(const PersonSet *ps1, const PersonSet *ps2)
{
  // You may call PersonSetIsSubset here!
  
  //Solution
  if (PersonSetIsSubset(ps1, ps2) == 1 && PersonSetIsSubset(ps2, ps1) == 1)
  {
    return 1;
  }

  return 0;
}
