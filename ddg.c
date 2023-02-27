#include "spkmeans.h"

double ** ddg(Vector * points, int n)
{
    double ** weighted = wam(points, n);
    double ** diagonal = calloc(n , sizeof (double *));
    int i, j;
    for (i = 0; i < n; i++)
    {
        diagonal[i] = calloc(n , sizeof (double));
        double sum = 0;
        for (j = 0; j < n; j++)
            sum += weighted[i][j];
        diagonal[i][i] = sum;
    }

    for (i = 0; i < n; i++)
    {
        printf("[");
        for (j = 0; j < n; j++)
            printf(" %.4f ", diagonal[i][j]);
        printf("]\n");
    }

    return diagonal;
}