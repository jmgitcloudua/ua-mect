#include <stdio.h>
#include <assert.h>
#include "deque.h"

int main()
{
    deque_type *d = deque_alloc();
    assert(d != NULL);

    for (int i = 1; i <= 256; i += i)
    {
        deque_push_back(d, i);
    }

    while (deque_is_empty(d) != true)
    {
        printf("%d\n", deque_pop_front(d));
    }

    deque_free(d);

    return 0;
}