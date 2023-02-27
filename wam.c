#include "spkmeans.h"

double calcDistance(Vector*,Vector*);

double** wam(Vector * head, int numpoints){
    Vector * curr1 = head;
    int row=0;
    int col=0;
    int i,j;
    Vector * curr2 = curr1;
    double ** matrix = calloc(numpoints, sizeof(double*));
    for(i=0;i<numpoints;i++){
        matrix[i] = calloc(numpoints, sizeof(double*));
    }

    while(curr1->cords != NULL){
        while(curr2->cords != NULL){
            if(curr1 == curr2) {
                matrix[row][row] = 0;
                col++;
                curr2 = curr2->next;
                continue;
            }
            double distance = calcDistance(curr1, curr2);
            double exponent = -1*(distance/2);
            matrix[row][col] = exp(exponent);
            col++;
            curr2 = curr2->next;
        }
        curr2 = head;
        col = 0;
        row++;
        curr1 = curr1->next;
    }
    for (i = 0; i < numpoints; i++)
    {
        printf("[");
        for (j = 0; j < numpoints; j++)
            printf(" %.6f ", matrix[i][j]);
        printf("]\n");
    }
    return matrix;
}

double calcDistance(Vector * point1,  Vector * point2){
    double diff = 0;
    struct cord * pointCords = point1->cords;
    struct cord * centroidCords = point2->cords;
    while(pointCords != NULL){
        diff += pow(pointCords->value - centroidCords->value, 2);
        pointCords = pointCords->next;
        centroidCords = centroidCords->next;
    }
    return diff;
}