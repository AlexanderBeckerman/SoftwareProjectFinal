#include "spkmeans.h"
double getDistance(double * , double * , int);
double* addVectors(double * v1, double * v2, int dim);

void kmeans(int iter, int k, double ** py_centroids, double ** py_points, int dim, int numpoints)
{

    double ** centroids = py_centroids;
    double ** vectors = py_points;
    int ** clusters;
    int i,j,m;
    int iterations = 0;
    double distance = 0, minDist = -1;
    int closest = 0;




    clusters = calloc(k, sizeof(int *));
    for(i=0; i < k; i++){
        clusters[i] = calloc(3*numpoints, sizeof(int));
        for(j=0;j < numpoints;j++){
            clusters[i][j] = -1;
        }
    }

    while(iterations < iter)
    {

        for(i=0; i < k; i++)
        {
            for(j=0; j < numpoints; j++){
                clusters[i][j] = -1;
            }
        }

        for(i = 0; i < numpoints; i++){
            for(j = 0; j < k; j++){
                distance = getDistance(vectors[i], centroids[j], dim);
                if(minDist == -1){
                    minDist = distance;
                    closest = j;
                    continue;
                }
                if(minDist > distance) {
                    closest = j;
                    minDist = distance;
                }
            }
            for(j = 0; j < k; j++){
                if(j == closest)
                    clusters[j][i] = 1;
                else
                    clusters[j][i] = -1;
            }
            minDist = -1;
        }

        for(j = 0; j < k; j++){
            int counter = 0;
            double * newCent = calloc(dim, sizeof(double));
            for(i = 0; i < numpoints; i++)
            {
                if(clusters[j][i] == 1){
                    counter++;
                    for(m=0;m<dim;m++)
                    {
                        newCent[m] = newCent[m] + vectors[i][m];
                    }
                }
            }
            if(counter != 0){
                for(m = 0; m < dim; m++){
                    centroids[j][m] = newCent[m] / counter;
                }
            }


            free(newCent);
        }

        iterations++;
    }

    for(i = 0; i < k; i++){
        for(j = 0; j < dim; j++){
            if (j < dim-1)
                printf("%.4f,", centroids[i][j]);
            else{
                printf("%.4f\n", centroids[i][j]);
            }
        }
    }


    for(i = 0; i < numpoints; i++){
        free(vectors[i]);
    }
    free(vectors);
    for(i = 0; i < k; i++){
        free(centroids[i]);
        free(clusters[i]);
    }
    free(centroids);
    free(clusters);

}

double getDistance(double * v1, double * v2, int dim){
    double dist = 0;
    int i;
    for(i=0;i<dim;i++){
        dist += pow(v1[i]-v2[i], 2);
    }
    return sqrt(dist);
}

double * addVectors(double * v1, double * v2, int dim){
    double * result = calloc(dim, sizeof(double));
    int i;
    for(i=0;i<dim;i++){
        result[i] = v1[i] + v2[i];
    }
    return result;
}