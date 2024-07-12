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

#include "BSTree.h"

// NOTE THAT:
// - Field capacity was eliminated.
// - Field size was eliminated, because size==BSTreeGetNumberOfNodes(...).

// Definition of the structure
struct _PersonSet_
{
  BSTree *persons; // points to a BSTree of Person pointers
};

// Comparison function to be used in generic BSTree.
// Comparison is based on Person ID
static int cmpP(const void *a, const void *b)
{
  Person *p1 = (Person *)a;
  Person *p2 = (Person *)b;
  int d = p1->id - p2->id;
  return (d > 0) - (d < 0);
}

// Print function to be used in generic BSTree.
static void printP(void *p) { PersonPrintf((Person *)p, ""); }

// Create a PersonSet.
PersonSet *PersonSetCreate()
{
  // You must allocate space for the struct and create an empty persons tree!
  //<--Solution
  PersonSet *ps = (PersonSet *)malloc(sizeof(*ps));
  if (ps == NULL)
  {
    return NULL;
  }
  ps->persons = BSTreeCreate(cmpP, (void *)printP);
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
  BSTreeDestroy(&((*pps)->persons));
  free(*pps);
  *pps = NULL;
  //-->
}

int PersonSetSize(const PersonSet *ps)
{
  return BSTreeGetNumberOfNodes(ps->persons);
}

int PersonSetIsEmpty(const PersonSet *ps) { return BSTreeIsEmpty(ps->persons); }

// Print function to use in PersonSetPrint
static void printlnP(void *p) { PersonPrintf((Person *)p, ";\n"); }

void PersonSetPrint(const PersonSet *ps)
{
  printf("{\n");
  BSTreeTraverseINOrder(ps->persons, printlnP);
  printf("}(size=%d)\n", PersonSetSize(ps));
}

// Find node in BSTree ps->persons of person with given id.
// Return a pointer to the stored Person instance.
// Or NULL, if it does not belong to the BSTree.
// (INTERNAL function.)
static Person *search(const PersonSet *ps, int id)
{
  Person dummyPerson;
  dummyPerson.id = id;
  return BSTreeSearch(ps->persons, &dummyPerson);
}

// Add person *p to *ps.
// Do nothing if *ps already contains a person with the same id.
void PersonSetAdd(PersonSet *ps, Person *p)
{
  //<--Solution
  BSTreeAdd(ps->persons, (void *)p);
  BSTreeTestInvariants(ps->persons);
  //-->
}

// Pop one person out of *ps.
Person *PersonSetPop(PersonSet *ps)
{
  assert(!PersonSetIsEmpty(ps));
  // It is easiest to pop and return the first person in the set!
  //<--Solution
  
  void *p;
  p = BSTreeGetMin(ps->persons);
  BSTreeRemove(ps->persons, p);
  BSTreeTestInvariants(ps->persons);
 
  return (Person *)p;
  //-->
}

// Remove the person with given id from *ps, and return it.
// If no such person is found, return NULL and leave set untouched.
Person *PersonSetRemove(PersonSet *ps, int id)
{
  // You may call search here!
  //<--Solution
  void *p;
  p = search(ps, id);
  if (p == NULL) // if not found
  {
    return NULL;
  }
  BSTreeRemove(ps->persons, p);
  BSTreeTestInvariants(ps->persons);
  return p;
  //-->
}

// Get the person with given id of *ps.
// return NULL if it is not in the set.
Person *PersonSetGet(const PersonSet *ps, int id)
{
  // You may call search here!
  //<--Solution
  return search(ps, id);
  //-->
}

// Return true (!= 0) if set contains person with given id, false otherwise.
int PersonSetContains(const PersonSet *ps, int id)
{
  return search(ps, id) != NULL;
}

// Return a NEW PersonSet with the union of *ps1 and *ps2.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetUnion(const PersonSet *ps1, const PersonSet *ps2)
{
  PersonSet *ps = PersonSetCreate();
  //<--Solution
  if (ps == NULL)
  {
    return NULL;
  }

  Queue *q1 = BSTreeGetItems(ps1->persons);
  Queue *q2 = BSTreeGetItems(ps2->persons);

  while (!QueueIsEmpty(q1))
  {
    void *p = QueueDequeue(q1);
    BSTreeAdd(ps->persons, p);
  }
  QueueDestroy(&q1);

  while (!QueueIsEmpty(q2))
  {
    void *p = QueueDequeue(q2);
    BSTreeAdd(ps->persons, p);
  }
  QueueDestroy(&q2);

  return ps;
  //-->
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
  Queue *q1 = BSTreeGetItems(ps1->persons);

  while (QueueIsEmpty(q1) == 0)
  {
    Person *p = QueueDequeue(q1);
    if (PersonSetContains(ps2, p->id))
    {
      PersonSetAdd(ps, p);
    }
  }
  QueueDestroy(&q1);
  return ps;
  //-->
}

// Return a NEW PersonSet with the set difference of *ps1 and *ps2.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetDifference(const PersonSet *ps1, const PersonSet *ps2)
{
  PersonSet *ps = PersonSetCreate();
  //<--Solution
  if (ps == NULL)
  {
    //PersonSetDestroy(&ps);
    return NULL;
  }
  Queue *q1 = BSTreeGetItems(ps1->persons);

  while (QueueIsEmpty(q1) == 0)
  {
    Person *p = QueueDequeue(q1);
    if (!PersonSetContains(ps2, p->id))
    {
      PersonSetAdd(ps, p);
    }
  }
  QueueDestroy(&q1);
  return ps;
  //-->
}

// Return true iff *ps1 is a subset of *ps2.
int PersonSetIsSubset(const PersonSet *ps1, const PersonSet *ps2)
{
  //<--Solution
  Queue *q1 = BSTreeGetItems(ps1->persons);
  while (QueueIsEmpty(q1) == 0)
  {
    Person *p = QueueDequeue(q1);
    if (!PersonSetContains(ps2, p->id))
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
  return PersonSetSize(ps1) == PersonSetSize(ps2) &&
         PersonSetIsSubset(ps1, ps2);
}
