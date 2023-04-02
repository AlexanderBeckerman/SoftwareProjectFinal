#include "spkmeans.h"

Vector * spk(Vector * points, int n, int k)
{

    double ** matrix = gl(points, n);
    matrix = jacobi(matrix, n, 0, k);
    return NULL;
}