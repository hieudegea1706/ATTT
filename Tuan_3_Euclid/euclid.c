#include <stdio.h>

#define MOD 0x409   // x^10 + x^3 + 1 = 10000001001 = 1033


int degree(int a)
{
    int deg = -1;
    while (a)
    {
        a >>= 1;
        deg++;
    }
    return deg;
}

int poly_div(int a, int b, int *rem)
{
    int da = degree(a);
    int db = degree(b);

    int q = 0;

    while (da >= db)
    {
        int shift = da - db;
        q ^= (1 << shift);
        a ^= (b << shift);

        da = degree(a);
    }

    *rem = a;
    return q;
}


int inverse(int a)
{
    int r0 = MOD;
    int r1 = a;

    int t0 = 0;
    int t1 = 1;

    printf("\n===== START =====\n");

    while (r1 != 0)
    {
        int r;
        int q = poly_div(r0, r1, &r);

        printf("r0 = %d, r1 = %d\n", r0, r1);
        printf("q = %d\n", q);
        printf("r = %d\n\n", r);

        r0 = r1;
        r1 = r;

        int t = t0 ^ (q * t1);

        t0 = t1;
        t1 = t;
    }

    printf("GCD = %d\n", r0);

    if (r0 != 1)
    {
        printf("No inverse\n");
        return -1;
    }

    return t0;
}

int main()
{
    int a = 523;
    int b = 1015;

    printf("Inverse of a = %d\n", inverse(a));
    printf("\n\n");

    printf("Inverse of b = %d\n", inverse(b));

    return 0;
}