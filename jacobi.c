#include "spkmeans.h"
double getOff(double **, int);
double **createP(double **, int);
double *getCandS(double **, int);
int *eigenGap(double *, int, int);
double **transform(double **, int);
int *findLargestValue(double **, int);
double **mult(double **, double **, int);
void freeMatrix(double **, int);

double **jacobi(double **L, int n, int flag, int k)
{
    int j;
    int i;
    int gap;
    int rotations = 0;
    int *eigenIndexes;
    double **result;
    double epsilon = 0.00001;
    double offset = getOff(L, n);
    double offsetDiff = epsilon + 1;
    double **V = createP(L, n);
    double *eigenValues = malloc(n * sizeof(double));

    while (offsetDiff > epsilon && rotations < 100)
    {
        if (rotations != 0)
            V = mult(V, createP(L, n), n);
        L = transform(L, n);
        offsetDiff = offset - getOff(L, n);
        offset = getOff(L, n);
        rotations++;
    }

    for (j = 0; j < n; j++)
    {
        eigenValues[j] = L[j][j];
        if (eigenValues[j] == -0.0)
        {
            for (i = 0; i < n; i++)
            {
                V[i][j] = -1 * V[i][j];
            }
            eigenValues[j] = 0;
        }
        if (flag == 1 && j < n - 1)
            printf("%.4f,", eigenValues[j]);
        else if (flag == 1 && j == n - 1)
            printf("%.4f\n", eigenValues[j]);
    }

    if (flag == 1)
    {
        return V;
    }

    eigenIndexes = eigenGap(eigenValues, n, k);

    gap = eigenIndexes[0];

    result = calloc(n + 1, sizeof(double *));
    result[0] = calloc(2, sizeof(double));
    result[0][0] = n;
    result[0][1] = gap;
    result++;
    for (i = 0; i < n; i++)
    {
        result[i] = calloc(gap, sizeof(double));
        for (j = 0; j < gap; j++)
            result[i][j] = V[i][eigenIndexes[j + 1]];
    }

    freeMatrix(V, n);
    freeMatrix(L, n);
    free(eigenIndexes);
    free(eigenValues);

    return result;
}

double getOff(double **a, int n)
{
    double sum = 0;
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            sum += i == j ? 0 : pow(a[i][j], 2);
        }
    }
    return sum;
}

double **transform(double **a, int n)
{
    int row, col;
    int k;
    int *iandj = findLargestValue(a, n);
    int i = iandj[0];
    int j = iandj[1];
    double *cands = getCandS(a, n);
    double c = cands[0];
    double s = cands[1];
    double **newA = calloc(n, sizeof(double *));
    for (row = 0; row < n; row++)
    {
        newA[row] = calloc(n, sizeof(double));
    }

    for (row = 0; row < n; row++)
    {
        for (col = 0; col < n; col++)
        {
            newA[row][col] = a[row][col];
        }
    }

    for (k = 0; k < n; k++)
    {
        newA[k][i] = (c * a[k][i]) - (s * a[k][j]);
        newA[i][k] = (c * a[k][i]) - (s * a[k][j]);

        newA[k][j] = (s * a[k][i]) + (c * a[k][j]);
        newA[j][k] = (s * a[k][i]) + (c * a[k][j]);
    }

    newA[i][j] = (c * c - s * s) * a[i][j] + s * c * (a[i][i] - a[j][j]);
    newA[i][i] = c * c * a[i][i] + s * s * a[j][j] - 2 * c * s * a[i][j];
    newA[j][j] = s * s * a[i][i] + c * c * a[j][j] + 2 * c * s * a[i][j];
    newA[j][i] = (c * c - s * s) * a[i][j] + s * c * (a[i][i] - a[j][j]);

    freeMatrix(a, n);
    free(iandj);
    free(cands);

    return newA;
}

double **mult(double **a, double **b, int n)
{
    double **result = calloc(n, sizeof(double *));
    int i, j, k;
    for (i = 0; i < n; i++)
    {
        result[i] = calloc(n, sizeof(double));
        for (j = 0; j < n; j++)
        {
            for (k = 0; k < n; k++)
            {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    freeMatrix(a, n);
    freeMatrix(b, n);

    return result;
}

double **createP(double **a, int n)
{
    int row;
    int *iandj = findLargestValue(a, n);
    int i = iandj[0];
    int j = iandj[1];
    double *cands = getCandS(a, n);
    double c = cands[0];
    double s = cands[1];
    double **matrix = calloc(n, sizeof(double *));

    for (row = 0; row < n; row++)
    {
        matrix[row] = calloc(n, sizeof(double));
        matrix[row][row] = 1;
    }

    matrix[i][i] = c;
    matrix[j][j] = c;
    matrix[i][j] = s;
    matrix[j][i] = -s;

    free(iandj);
    free(cands);
    return matrix;
}

int *findLargestValue(double **a, int n)
{
    double max = 0;
    int *indexes = calloc(2, sizeof(int));
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (i != j && max < fabs(a[i][j]))
            {
                max = fabs(a[i][j]);
                indexes[0] = i;
                indexes[1] = j;
            }

    return indexes;
}

double *getCandS(double **a, int n)
{
    int *iandj = findLargestValue(a, n);
    double *results;
    int i = iandj[0];
    int j = iandj[1];
    double aii = a[i][i];
    double aij = a[i][j];
    double ajj = a[j][j];
    double c = 0, theta = 0, s = 0, t = 0;
    int sign;

    theta = (ajj - aii) / (2 * aij);
    if (theta >= 0)
        sign = 1;
    else
        sign = -1;
    t = sign / (fabs(theta) + sqrt(theta * theta + 1));
    c = 1 / (sqrt((t * t) + 1));
    s = (t * c);
    results = calloc(2, sizeof(double));
    results[0] = c;
    results[1] = s;

    free(iandj);
    return results;
}
int compare(const void *a, const void *b)
{
    double x = *((double *)a);
    double y = *((double *)b);

    if (x == y)
        return 0;
    else if (x < y)
        return -1;
    else
        return 1;
}

int *eigenGap(double *eigenValues, int n, int k)
{
    double max = 0;
    int index = 0, i, j = 0;
    double *eigenCopy = calloc(n, sizeof(double));
    int *indexes;
    for (i = 0; i < n; ++i)
        eigenCopy[i] = eigenValues[i];
    qsort(eigenCopy, n, sizeof(double), compare);
    if (k == -1)
    {
        for (i = 0; i < n / 2; i++)
        {
            double gap = fabs(eigenCopy[i + 1] - eigenCopy[i]);
            if (max < gap)
            {
                max = gap;
                index = i;
            }
        }
        index++;

        indexes = calloc(index + 1, sizeof(int));
        indexes[0] = index;
    }
    else
    {
        indexes = calloc(k + 1, sizeof(int));
        indexes[0] = k;
        index = k;
    }

    for (i = 0; i < index; i++)
        for (j = 0; j < n; j++)
            if (eigenValues[j] == eigenCopy[i])
                indexes[i + 1] = j;

    free(eigenCopy);
    return indexes;
}

void freeMatrix(double **mat, int n)
{
    int i;
    for (i = 0; i < n; i++)
        free(mat[i]);
    free(mat);
}
