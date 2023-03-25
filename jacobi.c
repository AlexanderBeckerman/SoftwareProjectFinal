#include "spkmeans.h"
double getOff(double ** ,int);
double ** createP(double ** ,int);
double* getCandS(double **, int);
int eigenGap(double *  ,int);
double** transform(double ** ,int);
int* findLargestValue(double **  ,int);
double ** mult(double **, double ** ,int);

double ** jacobi(double ** L, int n)
{
    int j;
    int i;
    int gap;
    int rotations=0;
    double ** result;
    double ** newL;
    double epsilon = 0.00001;
    double offset = getOff(L, n);
    double offsetDiff = epsilon + 1;
    double ** V = createP(L, n);
    double * eigenValues = malloc(n* sizeof(double));

    while(offsetDiff > epsilon && rotations < 100){

        L = transform(L, n);
        offsetDiff = offset - getOff(L, n);
        offset = getOff(L, n);
        printf("\n");
        for (i = 0; i < n; i++)
        {
            printf("[");
            for (j = 0; j < n; j++)
                printf(" %.4f ", L[i][j]);
            printf("]\n");
        }
        rotations++;
        V = mult(V, createP(L, n), n);
    }

//    for (i = 0; i < n; i++)
//    {
//        printf("[");
//        for (j = 0; j < n; j++)
//            printf(" %.6f ", L[i][j]);
//        printf("]\n");
//    }


    for(j = 0; j < n; j++){
        eigenValues[j] = L[j][j];
        // printf("%f , ", eigenValues[j]);
    }

    gap = eigenGap(eigenValues, n);
    result = calloc(n, sizeof(double *));
    for (i = 0; i < n; i++){
        result[i] = calloc(gap, sizeof(double));
        for (j = 0; j < gap; j++) {
            result[i][j] = V[i][j];
            printf("%f", result[i][j]);
        }
        // printf("\n");
    }


    return result;
}

double getOff(double ** a , int n)
{
    double sum = 0;
    int i, j;
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++) {
            sum += i == j ? 0 : pow(a[i][j], 2);
        }
    }
    return sum;
}

double** transform(double ** a , int n)
{
    int row=0,col=0;
    int k = 0;
    int * iandj = findLargestValue(a, n);
    int i=iandj[0];
    int j=iandj[1];
    double* cands = getCandS(a, n);
    double c = cands[0];
    double s = cands[1];
    double ** newA = calloc(n, sizeof(double*));
    for(row=0;row<n;row++){
        newA[row] = calloc(n, sizeof(double));
    }

    for(row=0;row<n;row++) {
        for (col = 0; col < n; col++) {
            newA[row][col] = a[row][col];
        }
    }



    for (k = 0; k < n; k++)
    {
        newA[k][i] = (c*a[k][i]) - (s*a[k][j]);
        newA[i][k] = (c * a[k][i]) - (s * a[k][j]);

        newA[k][j] = (c*a[k][i]) + (s*a[k][j]);
        newA[j][k] = (c * a[k][i]) + (s * a[k][j]);
    }

    newA[i][j] = (c*c - s*s)*a[i][j] + s*c*(a[i][i] - a[j][j]);
    newA[i][i] = c*c*a[i][i] + s*s*a[j][j] - 2*c*s*a[i][j];
    newA[j][j] = s*s*a[i][i] + c*c*a[j][j] + 2*c*s*a[i][j];
    newA[j][i] = (c*c - s*s)*a[i][j] + s*c*(a[i][i] - a[j][j]);

//    for(row=0;row<n;row++){
//        for(col=0; col< n; col++){
//            if(row != i && row != j && col == i){
//                newA[row][i] = c*a[row][i] - s*a[row][j];
//                newA[i][row] = c*a[row][i] - s*a[row][j];
//            }
//            else if(row != i && row != j && col == j) {
//                newA[row][j] = c * a[row][j] + s * a[row][i];
//                newA[j][row] = c * a[row][j] + s * a[row][i];
//            }
//            else if(row == col && row == i){
//                newA[i][i] = c*c*a[i][i] + s*s*a[j][j] - 2*c*s*a[i][j];
//            }
//            else if(row == col && row == j){
//                newA[j][j] = s*s*a[i][i] + c*c*a[j][j] + 2*c*s*a[i][j];
//            }
//            else if(row == i && col == j){
//                newA[i][j] = (c*c - s*s)*a[i][j] + s*c*(a[i][i] - a[j][j]);
//            }
//            else{
//                newA[row][col] = a[row][col];
//            }
//        }
//    }

    return newA;

}

double ** mult(double ** a, double ** b , int n)
{
    double ** result = calloc(n , sizeof (double *));
    int i, j, k;
    for (i = 0; i < n; i++) {
        result[i] = calloc(n , sizeof (double));
        for (j = 0; j < n; j++) {
            int sum = 0;
            for (k = 0; k < n; k++) {
                sum += a[i][k] * b[k][j];
            }
            result[i][j] = sum;
        }
    }

    return result;
}

double ** createP(double ** a , int n)
{
    int row;
    int col;
    int * iandj = findLargestValue(a, n);
    int i = iandj[0];
    int j = iandj[1];
    double* cands = getCandS(a, n);
    double c = cands[0];
    double s = cands[1];
    double ** matrix = calloc(n, sizeof(double*));

    for(row=0;row<n;row++){
        matrix[row] = calloc(n, sizeof(double));
    }

    for(row=0; row < n; row++){
        for(col=0; col< n; col++){
            if(row == col){
                if(row == i || row == j){
                    matrix[row][col] = c;
                }
                else{
                    matrix[row][col] = 1;
                }
            }
            else{
                if(row == i && col == j)
                    matrix[row][col] = s;
                else if(row == j && col == i)
                    matrix[row][col] = -1*s;
                else
                    matrix[row][col] = 0;
            }
        }
    }

    return matrix;

}

int * findLargestValue(double ** a , int n)
{
    double max = 0;
    int * indexes = calloc(2, sizeof (int));
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

double* getCandS(double ** a, int n)
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
    return results;
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

int eigenGap(double * eigenValues , int n)
{
    double max = 0;
    int index, i = 0;
    qsort(eigenValues, n, sizeof (double), compare);
    for (i = 0; i < n / 2 ; i++)
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


