#include "spkmeans.h"


Vector * addVectors(Vector *, Vector *);
double calcDistance(Vector * , Vector *);
int assignPoint(Vector *, Vector ** , int);
void freeList(Vector *);
void freeVector(Vector *);


void kmeans(int iter, int k, Vector **py_centroids, Vector *py_points)
{
    Vector *head_vec;
    Vector *curr_vec;
    int i;
    Vector ** centroids;
    Vector ** clusters;
    int iterations = 0;
    clusters = calloc(k, sizeof(Vector));
    head_vec = py_points;
    centroids = py_centroids;

    while (iterations < iter) {
        for(i = 0;i < k ; i++){
            free(clusters[i]);
            clusters[i] = calloc(1, sizeof(Vector));
        }
        curr_vec = head_vec;
        while (curr_vec != NULL) {
            int closest = assignPoint(curr_vec, centroids, k);
            Vector *iterator = clusters[closest];
            if (iterator->cords) {
                while (iterator->next != NULL)
                    iterator = iterator->next;
                iterator->next = malloc(sizeof(Vector));
                *iterator->next = *curr_vec;
                iterator->next->next = NULL;
            }
            else {
                clusters[closest] = malloc(sizeof(Vector));
                *clusters[closest] = *curr_vec;
                clusters[closest]->next = NULL;
            }
            curr_vec = curr_vec->next;
        }
        for(i = 0;i < k ; i++){
            int counter = 1;
              Vector *iterator = clusters[i];
              Vector *newCent = malloc(sizeof(Vector));
            Cord * cordsIterator;
            if (iterator == NULL)
                continue;
            *newCent = *iterator;
            iterator = iterator->next;
            while(iterator != NULL){
                *newCent = *addVectors(newCent, iterator);
                iterator = iterator->next;
                counter++;
            }
            cordsIterator = newCent->cords;
            if (cordsIterator == NULL)
                continue;
            while (cordsIterator != NULL){
                cordsIterator->value = cordsIterator->value / counter;
                cordsIterator = cordsIterator->next;
            }

            *centroids[i] = *newCent;
            free(newCent);
        }
        iterations++;
    }

    for (i = 0;i < k; i++)
    {
        Cord * printIter = centroids[i]->cords;
        while (printIter != NULL)
        {
            printf("%.4f", printIter->value);
            printIter = printIter->next;
            if (printIter != NULL)
                printf(",");
        }
        printf("\n");
    }
}


double calcDistance(Vector * point, Vector * centroid){
    double diff = 0;
    Cord * pointCords = point->cords;
    Cord * centroidCords = centroid->cords;
    while(pointCords != NULL){
        diff += pow(pointCords->value - centroidCords->value, 2);
        pointCords = pointCords->next;
        centroidCords = centroidCords->next;
    }
    diff = sqrt(diff);
    return diff;
}

int assignPoint(Vector * point, Vector ** centroids, int k){
    double mindist = -1;
    int i=0;
    int minind = 0;
    for(;i<k;i++){

        double dist = calcDistance(point, centroids[i]);
        if(mindist == -1){
            mindist = dist;
            minind = i;
        }
        else if(dist < mindist){
            mindist = dist;
            minind=i;
        }
    }
    return minind;
}

  Vector * addVectors(Vector * v1, Vector * v2){
      Vector * res = malloc(sizeof(Vector));
    Cord * resCord;
    Cord * v1Cord;
    Cord * v2Cord;
    res->cords = malloc(sizeof (Cord));
    res->next = NULL;
    resCord = res->cords;
    v1Cord = v1->cords;
    v2Cord = v2->cords;
    while(v1Cord != NULL){
        resCord->value = v1Cord->value + v2Cord->value;
        resCord->next = malloc(sizeof (Cord));
        v1Cord = v1Cord->next;
        v2Cord = v2Cord->next;
        if (v1Cord == NULL)
            resCord->next = NULL;
        else
            resCord = resCord->next;

    }
    return res;
}

void freeList(Vector *list)
{
    Vector * iterator = list;
    Vector * temp;
    while (iterator != NULL)
    {
        temp = iterator;
        iterator = iterator->next;
        freeVector(temp);
    }
}

void freeVector(Vector *vec)
{
    Cord * iterator = vec->cords;
    Cord * temp;
    while (iterator != NULL)
    {
        temp = iterator;
        iterator = iterator->next;
        free(temp);
    }
}