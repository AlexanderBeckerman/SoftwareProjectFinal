#include "project_header.h"

int main()
{
    printf("hello %f", 0.5);
//    int ** a = calloc(3*3, sizeof (int));
//    a[1][1] = 5;
//    a[0][1] = 7;
//    a[2][2] = 1;
//    printf("\n%d\n", a[1][1]);
//    int i;
//    for (i = 0; i < 3; ++i) {
//        printf("\n%d , %d , %d" , a[i][0] , a[i][1] , a[i][2]);
//    }

    return 0;
}

double ** ddg(int n, Vector *points)
{
    double ** weighted = wam(points, n);
    double diagonal[n][n];
    memset( diagonal , 0, sizeof(double) );
    int i, j;
    for (i = 0; i < n; i++)
    {
        double sum = 0;
        for (j = 0; j < n; j++)
            sum += weighted[i][j];
        diagonal[i][i] = sum;
    }

    return diagonal;
}