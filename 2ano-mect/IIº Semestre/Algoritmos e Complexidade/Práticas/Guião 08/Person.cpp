/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Algoritmo e Complexidade | 2º Ano-2º semestre
 * Curso: MIECT  
 * Maio 2021
 */

// Complete the functions (marked by ...)
// so that it passes all tests in PersonTest.

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Person.h"

// This variable stores the last ID that was assigned to a Person.
// It should be used to assign serial, unique IDs automatically upon creation.
// The first person will have id=1, the second id=2, etc.
static int lastID = 0;

// Alocate and store a Person.
// Returns the pointer to the new structure,
// or NULL if allocation fails.
// The names are copied to internally allocated memory.
Person *PersonCreate(const char *fname, const char *lname, int yy, int mm, int dd)
{

  Person *p = (Person *)malloc(sizeof(*p)); // allocation for person;

  if (p == NULL)
  {
    return NULL;
  }
  char *fn = (char *)malloc(strlen(fname));
  char *ln = (char *)malloc(strlen(lname));
  ;
  if (fn == NULL && ln == NULL)
  {
    return NULL;
  }

  p->firstName = strcpy(fn, fname);
  p->lastName = strcpy(ln, lname);
  p->birthDate.year = yy;
  p->birthDate.month = mm;
  p->birthDate.day = dd;
 
 lastID++;
 p->id = lastID;
    
  

  return p;
}

// Free the memory pointed to by *pp and by the names inside it,
// and invalidate *pp contents.
// Precondition: *pp must not be NULL.
// Postcondition: *pp is set to NULL.
void PersonDestroy(Person **pp)
{
  assert(*pp != NULL);
  free(*pp);
  *pp = NULL;
}

// Prints a person formatted as "[id, lastname, firstname, birthdate]",
// followed by a suffix string.
void PersonPrintf(Person *p, const char *suffix)
{

  if (p == NULL)
  {
    printf("NULL%s", suffix);
  }
  else
  {

    printf("(%d, %s, %s, %s)%s",
           p->id, p->lastName, p->firstName,
           DateFormat(&(p->birthDate), YMD), suffix);
  }
}

// Compare birth dates of two persons.
// Return a negative/positive integer if p1 was born before/after p2.
// Return zero if p1 and p2 were born on the same date.
int PersonCompareByBirth(const Person *p1, const Person *p2)
{

  /*int res = (int)p1->birthDate.year - (int)p2->birthDate.year;
  if (res != 0)
  {
    return res;
  }
  res = (int)p1->birthDate.month - (int)p1->birthDate.month;
  if (res != 0)
  {
    return res;
  }
  res = (int)p1->birthDate.day - (int)p1->birthDate.day;
  return res;*/
  return DateCompare(&(p1->birthDate), &((p2->birthDate)));
}

// Compare two persons by last name, then first name (if last name is the same).
// Return a -/+/0 integer if p1 precedes/succeeds/is equal to p2.
int PersonCompareByLastFirstName(const Person *p1, const Person *p2)
{
  int res = strcmp(p1->lastName, p2->lastName);
  if (res == 0)
  {
    return 0;
  }
  return res;
}
