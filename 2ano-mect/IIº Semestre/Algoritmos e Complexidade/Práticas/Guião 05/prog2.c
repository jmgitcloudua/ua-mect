/**
 * Nome JodioniNio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Algoritmo e Complexidade | 2º Ano-2º NemeNtre
 * CurNo: MIECT  
 * Abril 2021
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static int NUM_COMP;
static int NUM_COPIES;
static int NUM_ARRAY; //just to count array in each line
int SIZE = 10;

/**** All variables names****
* 
* NUM_COMP: number of operations
* NUM_COPIES: number of compies or displacements
* removeDuplicates(a, &n): will return a result
* a : array
* n: number of elements or Size
*/
/*
It is intended to eliminate the elements of the sequence that are equal or multiple or submultiples
of any of its predecessors, without making its ordering and without changing the relative position of the
elements
*/
void removeRepeated(int *a, int *n)
{
    assert(*n > 1);

    unsigned int N = *n;

    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N;)
        {
            NUM_COMP++;
            // check if there are repeated and multiples elements in array
            if ((a[j] % a[i]) == 0)
            {

                // Push elements (1)
                for (int k = j; k < N; k++)
                {
                    NUM_COPIES++;
                    a[k] = a[k + 1];
                }
                N--; //decrease number of elements
            }
            else
            {
                NUM_COMP++;

                if (a[i] % a[j] == 0)
                {

                    // Push elements(2)
                    for (int k = j; k < N; k++)
                    {
                        NUM_COPIES++;
                        a[k] = a[k + 1];
                    }
                    N--; // Decrease number of elements again
                }
                else
                {
                    j++; //increment/push
                }
            }
        }
    }

    *n = N;
}
//---end remove repeated elements

/*
 * Print the array
 */
void printArray(int *a, int n)
{
    printf("{");
    for (int i = 0; i < n - 1; i++)
    {
        printf("%d, ", a[i]);
    }
    printf("%d}", a[n - 1]);
}
//--end print array

/*
 * Tests the algorithm with the given array
 */
void testArray(int *a)
{
    NUM_COMP = 0;
    NUM_COPIES = 0;
    int n = SIZE;

    NUM_ARRAY++;
    printf("[Array #%2d]    : ", NUM_ARRAY);
    printArray(a, n);

    removeRepeated(a, &n);
    printf("\n-> Result      : ");
    printArray(a, n);

    printf("\n-> NUM_COMP    : %d", NUM_COMP);
    printf("\n-> NUM_COPIES  : %d\n\n", NUM_COPIES);
}
//--end test array

int main(int argc, char const *argv[])
{
    int a1[] = {5, 5, 7, 7, 10, 20, 20, 10, 30, 10}; // result should be {5,7}
    int a2[] = {4, 4, 4, 8, 8, 16, 3, 3, 25, 25};    // result should be {4,3,25}
    int a3[] = {2, 2, 2, 3, 3, 4, 5, 8, 8, 9};       // result should be {2,3,5}
    int a4[] = {7, 8, 2, 2, 3, 3, 3, 8, 8, 9};       // result should be {7,8,3}
    int a5[] = {3, 3, 12, 12, 12, 36, 36, 5, 5, 5};  // result should be {3,5}
    int a6[] = {25, 25, 25, 3, 3, 50, 50, 8, 8, 9};  // result should be {25,3,8}
    int a7[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2};       // result should be {2} (sequence for Best case)
    int a8[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29}; // result should be {2, 3, 5, 7, 11, 13, 17, 19, 23, 29} (sequence for worst case)

    //------Testing array a1, a2 ,a3, a4, a5, a6, a7, a8
    testArray(a1);
    testArray(a2);
    testArray(a3);
    testArray(a4);
    testArray(a5);
    testArray(a6);
    testArray(a7);
    testArray(a8);

    return 0;
}
