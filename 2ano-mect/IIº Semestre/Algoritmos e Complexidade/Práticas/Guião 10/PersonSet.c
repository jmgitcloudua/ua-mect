/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Algoritmo e Complexidade | 2º Ano-2º semestre
 * Curso: MIECT  
 * Maio 2021
 */

// Complete the functions (marked by ...)
// so that it passes all tests in Tests.

#include "PersonSet.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SortedList.h"

// NOTE THAT:
// - Field capacity was eliminated.
// - Field size was eliminated, because size==ListGetSize(...).

// Definition of the structure
struct _PersonSet_
{
  List *persons; // points to a SortedList of Person pointers
};

// Comparison function to be used in generic SortedList.
// Comparison is based on Person ID
static int cmpP(const void *a, const void *b)
{
  Person *p1 = (Person *)a;
  Person *p2 = (Person *)b;
  int d = p1->id - p2->id;
  return (d > 0) - (d < 0);
}

// Create a PersonSet.
PersonSet *PersonSetCreate()
{
  // You must allocate space for the struct and create an empty persons list!

  //<--Solution
  PersonSet *ps = (PersonSet *)malloc(sizeof(*ps));
  if (ps == NULL)
  {
    return NULL;
  }
  ps->persons = ListCreate(cmpP);
  if (ps->persons == NULL)
  {
    free(ps);
    return NULL;
  }

  return ps;
  //-->
}

// Destroy PersonSet *pps
void PersonSetDestroy(PersonSet **pps)
{
  assert(*pps != NULL);
  //<--Solution
  ListDestroy(&((*pps)->persons));
  free(*pps);
  *pps = NULL;
  //-->
}

int PersonSetSize(const PersonSet *ps) { return ListGetSize(ps->persons); }

int PersonSetIsEmpty(const PersonSet *ps) { return ListIsEmpty(ps->persons); }

void PersonSetPrint(const PersonSet *ps)
{
  printf("{\n");
  for (ListMoveToHead(ps->persons); ListCurrentIsInside(ps->persons);
       ListMoveToNext(ps->persons))
  {
    Person *p = (Person *)ListGetCurrentItem(ps->persons);
    PersonPrintf(p, ";\n");
  }
  printf("}(size=%d)\n", PersonSetSize(ps));
  ListTestInvariants(ps->persons);
}

// Find node in list ps->persons of person with given id.
// (INTERNAL function.)
static int search(const PersonSet *ps, int id)
{
  Person dummyperson;
  dummyperson.id = id;
  return ListSearch(ps->persons, &dummyperson);
}

// Add person *p to *ps.
// Do nothing if *ps already contains a person with the same id.
void PersonSetAdd(PersonSet *ps, Person *p)
{
  //<--Solution

  ListInsert(ps->persons, (void *)p);
  ListTestInvariants(ps->persons);

  //-->
}

// Pop one person out of *ps.
Person *PersonSetPop(PersonSet *ps)
{
  assert(!PersonSetIsEmpty(ps));
  // It is easiest to pop and return the person in the first position!
  //<--Solution
  Person *p; //(Person *)malloc(sizeof(*p));

  p = ListRemoveTail(ps->persons);
  ListTestInvariants(ps->persons);

  return p;
  //-->
}

// Remove the person with given id from *ps, and return it.
// If no such person is found, return NULL and leave set untouched.
Person *PersonSetRemove(PersonSet *ps, int id)
{
  // You may call search here!
  //<--Solution
  Person *p;
  int i = search(ps, id);
  if (i == -1) // if not found
  {
    return NULL;
  }
  p = (Person *)ListRemoveCurrent(ps->persons);
  ListTestInvariants(ps->persons);

  return p;
  //-->
}

// Get the person with given id of *ps.
// return NULL if it is not in the set.
Person *PersonSetGet(const PersonSet *ps, int id)
{
  // You may call search here!
  //<--Solution
  Person *p;
  int i = search(ps, id);
  if (i == -1) // if not found
  {
    return NULL;
  }
  p = (Person *)ListGetCurrentItem(ps->persons);
  ListTestInvariants(ps->persons);

  return p;
  //-->
}

// Return true (!= 0) if set contains person wiht given id, false otherwise.
int PersonSetContains(const PersonSet *ps, int id)
{
  return search(ps, id) >= 0;
}

// Return a NEW PersonSet with the union of *ps1 and *ps2.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetUnion(const PersonSet *ps1, const PersonSet *ps2)
{
  PersonSet *ps = PersonSetCreate();

  // Merge the two sorted lists (similar to mergesort).
  for (ListMoveToHead(ps1->persons); ListCurrentIsInside(ps1->persons); ListMoveToNext(ps1->persons))
  {
    ListInsert(ps->persons, ListGetCurrentItem(ps1->persons));
  }

  for (ListMoveToHead(ps2->persons); ListCurrentIsInside(ps2->persons); ListMoveToNext(ps2->persons))
  {
    ListInsert(ps->persons, ListGetCurrentItem(ps2->persons));
  }

  return ps;
}

// Return a NEW PersonSet with the intersection of *ps1 and *ps2.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetIntersection(const PersonSet *ps1, const PersonSet *ps2)
{
  PersonSet *ps = PersonSetCreate();
  //<--Solution

  if (ps == NULL)
  {
    PersonSetDestroy(&ps);
    return NULL;
  }

  for (int i = 0; i < ListGetSize(ps1->persons); i++)
  {
    ListMove(ps1->persons, i);
    if (PersonSetContains(ps2, ((Person *)ListGetCurrentItem(ps1->persons))->id))
    {
      PersonSetAdd(ps, ListGetCurrentItem(ps1->persons));
    }
  }

  //-->

  return ps;
}

// Return a NEW PersonSet with the set difference of *ps1 and *ps2.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetDifference(const PersonSet *ps1, const PersonSet *ps2)
{
  PersonSet *ps = PersonSetCreate();
  //<--Solution
  for (int i = 0; i < ListGetSize(ps1->persons); i++)
  {
    ListMove(ps1->persons, i);
    if (search(ps2, ((Person *)ListGetCurrentItem(ps1->persons))->id) == -1)
    {
      PersonSetAdd(ps, ListGetCurrentItem(ps1->persons));
    }
  }
  //-->
  return ps;
}

// Return true iff *ps1 is a subset of *ps2.
int PersonSetIsSubset(const PersonSet *ps1, const PersonSet *ps2)
{
  //<--Solution
  int i;
  for (i = 0; i < ListGetSize(ps1->persons); i++)
  {
    ListMove(ps1->persons, i);

      if (!PersonSetContains(ps2, ((Person *)ListGetCurrentItem(ps1->persons))->id))
      {
      return 0;
      }
  }
  return 1;
  //-->
}

// Return true if the two sets contain exactly the same elements.
int PersonSetEquals(const PersonSet *ps1, const PersonSet *ps2)
{
  // You may call PersonSetIsSubset here!
  //<--Solution
  if (PersonSetIsSubset(ps1, ps2) == 1 && PersonSetIsSubset(ps2, ps1) == 1)
  {
    return 1;
  }

  return 0;
  //-->
}
