#include "spkmeans.h"


Vector * addVectors(Vector *, Vector *, int);
double calcDistance(Vector * , Vector *);
int assignPoint(Vector *, Vector ** , int);
void freeList(Vector *, int);
void freeArray(Vector **, int, int);
void freeVector(Vector *);



void kmeans(int iter, double epsilon, int k, Vector **py_centroids, Vector *py_points)
{
    Vector *head_vec;
    Vector *curr_vec;
    int i;
    double EPSILON = epsilon;
    Vector ** centroids;
    Vector ** clusters;
    int iterations = 0;
    double maxDist = EPSILON + 1;
    clusters = calloc(k, sizeof(Vector));
    head_vec = py_points;
    centroids = py_centroids;

    while (iterations < iter && maxDist >= EPSILON) {
        freeArray(clusters, k, 2);
        clusters = calloc(k, sizeof(Vector));
        curr_vec = head_vec;
        maxDist = 0;
        while (curr_vec != NULL) {
            int closest = assignPoint(curr_vec, centroids, k);
            Vector *iterator = clusters[closest];
            if (iterator && iterator->cords) {
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
            Vector *newCent;
            Cord * cordsIterator;
            double updatedDist;
            if (iterator == NULL)
                continue;
            newCent = iterator;
            iterator = iterator->next;
            while(iterator != NULL){
                newCent = addVectors(newCent, iterator, newCent == clusters[i]);
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
            updatedDist = calcDistance(centroids[i], newCent);
            maxDist =  updatedDist > maxDist ? updatedDist : maxDist;
            centroids[i] = newCent;
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

    freeList(py_points, 1);
    freeArray(py_centroids, 3, 0);
    free(clusters);
}


double calcDistance(Vector * point, Vector * centroid){
    double diff = 0;
    Cord * pointCords = point->cords;
    Cord *centroidCords = NULL;
    if (centroid != NULL) {
        centroidCords = centroid->cords;
    }
    while(pointCords != NULL && centroidCords != NULL && pointCords->value && centroidCords->value){
        diff += pow(pointCords->value - centroidCords->value, 2);
        pointCords = pointCords->next;
        centroidCords = centroidCords->next;
    }
    diff = sqrt(diff);
    return diff;
}

int assignPoint(Vector * point, Vector ** centroids, int k){
    double mindist = -1;
    int i;
    int minind = 0;
    for(i = 0; i < k; i++){
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

Vector * addVectors(Vector * v1, Vector * v2, int flag){
    Vector * res = calloc(1, sizeof(Vector));
    Cord * resCord;
    Cord * v1Cord;
    Cord * v2Cord;
    if (v1 == NULL || v2 == NULL || !v1->cords || !v2->cords) {
        if (v1 == NULL || !v1->cords)
            return v2;
        else
            return v1;
    }
    res->cords = calloc(1, sizeof (Cord));
    res->next = NULL;
    resCord = res->cords;
    v1Cord = v1->cords;
    v2Cord = v2->cords;
    while(v1Cord != NULL){
        resCord->value = v1Cord->value + v2Cord->value;
        resCord->next = calloc(1, sizeof (Cord));
        v1Cord = v1Cord->next;
        v2Cord = v2Cord->next;
        if (v1Cord == NULL)
            resCord->next = NULL;
        else
            resCord = resCord->next;

    }

    if (flag == 0)
        freeVector(v1);
    return res;
}

void freeList(Vector *list, int flag)
{
    Vector * iterator = list;
    Vector * temp;
    while (iterator != NULL)
    {
        temp = iterator;
        iterator = iterator->next;
        if (flag == 1)
            freeVector(temp);
        else
            free(temp);
    }
}

void freeArray(Vector **arr, int n, int flag)
{
    int i;
    Vector * iterator;
    for (i = 0; i < n; ++i) {
        iterator = arr[i];
        if (flag == 1)
            freeVector(iterator);
        else if (flag == 0)
            freeList(iterator, 1);
        else
            free(iterator);
    }
    free(arr);
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
    free(vec);
}


