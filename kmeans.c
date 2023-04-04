#include "spkmeans.h"


Vector * addVectors(Vector *, Vector *);
double calcDistance(Vector * , Vector *);
int assignPoint(Vector *, Vector ** , int);
void freeList(Vector *);
void freeVector(Vector *);


void kmeans(int iter, int k, Vector **py_centroids, Vector *py_points)
{
    struct vector *head_vec;
    struct vector *curr_vec;
    int i;
    struct vector ** centroids;
    struct vector ** clusters;
    int iterations = 0;
    clusters = calloc(k, sizeof(struct vector));
    head_vec = py_points;
    centroids = py_centroids;

    while (iterations < iter) {
        for(i = 0;i < k ; i++){
            free(clusters[i]);
            clusters[i] = calloc(1, sizeof(struct vector));
        }
        curr_vec = head_vec;
        while (curr_vec != NULL) {
            int closest = assignPoint(curr_vec, centroids, k);
            struct vector *iterator = clusters[closest];
            if (iterator->cords) {
                while (iterator->next != NULL)
                    iterator = iterator->next;
                iterator->next = malloc(sizeof(struct vector));
                *iterator->next = *curr_vec;
                iterator->next->next = NULL;
            }
            else {
                clusters[closest] = malloc(sizeof(struct vector));
                *clusters[closest] = *curr_vec;
                clusters[closest]->next = NULL;
            }
            curr_vec = curr_vec->next;
        }
        for(i = 0;i < k ; i++){
            int counter = 1;
            struct vector *iterator = clusters[i];
            struct vector *newCent = malloc(sizeof(struct vector));
            struct cord * cordsIterator;
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
        struct cord * printIter = centroids[i]->cords;
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
    struct cord * pointCords = point->cords;
    struct cord * centroidCords = centroid->cords;
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

struct vector * addVectors(Vector * v1, Vector * v2){
    struct vector * res = malloc(sizeof(struct vector));
    struct cord * resCord;
    struct cord * v1Cord;
    struct cord * v2Cord;
    res->cords = malloc(sizeof (struct cord));
    res->next = NULL;
    resCord = res->cords;
    v1Cord = v1->cords;
    v2Cord = v2->cords;
    while(v1Cord != NULL){
        resCord->value = v1Cord->value + v2Cord->value;
        resCord->next = malloc(sizeof (struct cord));
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
    struct vector * iterator = list;
    struct vector * temp;
    while (iterator != NULL)
    {
        temp = iterator;
        iterator = iterator->next;
        freeVector(temp);
    }
}

void freeVector(Vector *vec)
{
    struct cord * iterator = vec->cords;
    struct cord * temp;
    while (iterator != NULL)
    {
        temp = iterator;
        iterator = iterator->next;
        free(temp);
    }
}