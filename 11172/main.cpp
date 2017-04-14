#include <cstdio>

char GetComparatorChar(long a, long b)
{
    return a == b ? '=' : (a < b ? '<' : '>');
}

int main()
{
    int t; // num test cases
    long a = 0, b = 0;
    char buf[1];
    char *comp = buf;

    scanf("%d", &t);
    if (t <= 0) return 1;

    for (int i = 0; i < t; ++i)
    {
        scanf("%ld %ld", &a, &b);
        comp[0] = GetComparatorChar(a, b);
        printf("%s\n", comp);
    }
}

