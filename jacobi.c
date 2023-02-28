#include "spkmeans.h"

int* getCandS(double **);
int* findLargestValue(double ** );

double ** jacobi(Vector * points, int n)
{
    double epsilon;
}

double getOff(double ** a) // y
{

}

double** transform(double ** a, double ** p, int numpoints) // s
{
    int row=0,col=0;
    int * iandj = findLargestValue(a);
    int i=iandj[0];
    int j=iandj[1];
    int* cands = getCandS(a);
    double c = cands[0];
    double s = cands[1];
    double ** newA = calloc(numpoints, sizeof(double*));
    for(row=0;row<numpoints;row++){
        newA[row] = calloc(numpoints, sizeof(double*));
    }
    for(row=0;row<numpoints;row++){
        for(col=0; col< numpoints; col++){
            if(row != i && row != j && col == i){
                newA[row][i] = c*a[row][i] - s*a[row][j];
            }
            else if(row != i && row != j && col == j){
                newA[row][j] = c*a[row][j] + s*a[row][i];
            }
            else if(row == col && row == i){
                newA[i][i] = c*c*a[i][i] + s*s*a[j][j] - 2*c*s*a[i][j];
            }
            else if(row == col && row == j){
                newA[j][j] = s*s*a[i][i] + c*c*a[j][j] + 2*c*s*a[i][j];
            }
            else if(row == i && col == j){
                newA[i][j] = (c*c - s*s)*a[i][j] + s*c*(a[i][i] - a[j][j]);
            }
            else{
                newA[row][col] = a[row][col];
            }

        }
    }

    return newA;

}

void mult(double ** a, double ** b) // y
{

}

double ** createP(double ** a, int i, int j, int numpoints) // s
{
    int row;
    int col;
    int* cands = getCandS(a);
    double c = cands[0];
    double s = cands[1];

    double ** matrix = calloc(numpoints, sizeof(double*));
    for(row=0;row<numpoints;row++){
        matrix[i] = calloc(numpoints, sizeof(double*));
    }
    for(row=0; row < numpoints; row++){
        for(col=0; col< numpoints; col++){
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

int* findLargestValue(double ** a) // y
{

}

int* getCandS(double ** a) // s
{
    int * iandj = findLargestValue(a);
    int i=iandj[0];
    int j=iandj[1];
    double aii = a[i][i];
    double aij = a[i][j];
    double ajj = a[j][j];
    double c=0,theta=0,s=0,t=0;
    int sign;

    theta = (ajj - aii)/(2*aij);
    if(theta >= 0)
        sign = 1;
    else
        sign = -1;
    t = sign/(fabs(theta) + sqrt(theta*theta + 1));
    c = 1/(sqrt(t*t + 1));
    s = t*c;
    int * results = calloc(2, sizeof(double));
    results[0] = c;
    results[1] = s;
    return results;


}

int eigenGap(int * eigenValuse) // y
{

}
