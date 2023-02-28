#include "spkmeans.h"

int N; // size of the matrix jacobi gets (so we dont have to pass it to every function)

double ** jacobi(Vector * points, int n)
{
    N = n;
    double epsilon;
}

double getOff(double ** a) // y
{
    double sum = 0;
    int i, j;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            sum += i == j ? 0 : pow(a[i][j] , 2);
    return sum;
}

void transform(double ** a, double ** p) // s
{

}

double ** mult(double ** a, double ** b) // y
{
    double ** result = calloc(N , sizeof (double *));
    int i, j, k;
    for (i = 0; i < N; i++) {
        result[i] = calloc(N , sizeof (double));
        for (j = 0; i < N; i++) {
            int sum = 0;
            for (k = 0; i < N; i++) {
                sum += a[i][k] * b[k][j];
            }
            result[i][j] = sum;
        }
    }

    return result;
}

double ** createP(int i, int j) // s
{

}

int * findLargestValue(double ** a) // y
{
    double max = 0;
    int * indexes = calloc(2, sizeof (int));
    int i, j;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            if (i != j && max < fabs(a[i][j]))
            {
                max = fabs(a[i][j]);
                indexes[0] = i;
                indexes[1] = j;
            }

    return indexes;
}

int * getCT(double ** a) // s
{

}

int compare(const void * a, const void * b)
{
    double x = *((double *)a);
    double y = *((double *)b);

    if ( x == y )
        return 0;
    else if ( x < y )
        return -1;
    else
        return 1;
}

int eigenGap(double * eigenValues) // y
{
    double max = 0;
    int index, i = 0;
    qsort(eigenValues, N, sizeof (double), compare);
    for (i = 0; i < N / 2 ; i++)
    {
        double gap = max < eigenValues[i + 1] - eigenValues[i];
        if (max < gap)
        {
            max = gap;
            index = i;
        }
    }

    return index;
}


