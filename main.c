#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "project_header.h"


int main(int argc, char *argv[]) {

    char * command = argv[1];
    char * filename = argv[2];
    double n;
    int numpoints=0;
    char c;
    struct vector *head_vec;
    struct vector *curr_vec;
    struct cord *head_cord;
    struct cord *curr_cord;

    FILE* file = fopen(filename, "r");
    if(file == NULL){
        printf("open file error");
        return 0;
    }

    head_cord = malloc(sizeof( Cord));
    curr_cord = head_cord;
    curr_cord->next = NULL;

    head_vec = malloc(sizeof( Vector));
    curr_vec = head_vec;
    curr_vec->next = NULL;

    while(fscanf(file, "%lf%c", &n, &c) == 2){
        if (c == '\n')
        {
            numpoints++;
            curr_cord->value = n;
            curr_vec->cords = head_cord;
            curr_vec->next = malloc(sizeof( Vector));
            curr_vec = curr_vec->next;
            curr_vec->next = NULL;
            curr_vec->cords = NULL;
            head_cord = malloc(sizeof( Cord));
            curr_cord = head_cord;
            curr_cord->next = NULL;
            continue;
        }

        curr_cord->value = n;
        curr_cord->next = malloc(sizeof( Cord));
        curr_cord = curr_cord->next;
        curr_cord->next = NULL;
    }


    fclose(file);
    printf("Hello, World!\n");
    return 0;
}
