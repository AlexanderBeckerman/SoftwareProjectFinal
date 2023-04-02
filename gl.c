#include "spkmeans.h"

double ** gl(Vector * points, int n)
{
    double ** weighted = wam(points, n);
    double ** diagonal = ddg(points, n);
    double ** laplacian = calloc(n , sizeof (double *));

    int i, j;
    for (i = 0; i < n; i++)
    {
        laplacian[i] = calloc(n , sizeof (double));
        for (j = 0; j < n; j++)
            laplacian[i][j] = diagonal[i][j] - weighted[i][j];
    }

    return laplacian;
}