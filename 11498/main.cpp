#include <cstdio>
#include <cstring>

static const char *R_DIVISA = "divisa";
static const char *R_NO = "NO";
static const char *R_NE = "NE";
static const char *R_SE = "SE";
static const char *R_SO = "SO";

int main()
{
    int K = 1;        // Number of queries
    int N = 0, M = 0; // Division point
    int X = 0, Y = 0; // Query coordinates
    char buf[] = "divisa";
    char *result = buf;

    scanf("%d", &K);

    while (K > 0)
    {
        scanf("%d %d", &N, &M);
        
        for (int i = 0; i < K; ++i)
        {
            scanf("%d %d", &X, &Y);
            if (X == N || Y == M)
            {
                strncpy(result, R_DIVISA, sizeof(result));
            }
            else if (X < N && Y > M)
            {
                strncpy(result, R_NO, sizeof(result));
            }
            else if (X > N && Y > M)
            {
                strncpy(result, R_NE, sizeof(result));
            }
            else if (X > N && Y < M)
            {
                strncpy(result, R_SE, sizeof(result));
            }
            else if (X < N && Y < M)
            {
                strncpy(result, R_SO, sizeof(result));
            }

            printf("%s\n", result);
        }

        // Start next test case (or end of input).
        scanf("%d", &K);
    }
}
