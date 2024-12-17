#include <stdio.h>

typedef struct ep_complex
{
    double real;
    double imag;
} ep_complex_t;

ep_complex_t ep_complex_add(ep_complex_t a, ep_complex_t b)
{
    ep_complex_t c;
    c.real = a.real + b.real;
    c.imag = a.imag + b.imag;
    return c;
}

int main()
{
    ep_complex_t a = {1.0, 2.0};
    ep_complex_t b = {3.0, 4.0};
    ep_complex_t c = ep_complex_add(a, b);
    printf("c.real = %.2f, c.imag = %.2f, C = %.2f + %.2fi\n", c.real, c.imag, c.real, c.imag);
    return 0;
}

