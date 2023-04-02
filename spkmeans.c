#include "spkmeans.h"


int main(int argc, char *argv[]) {

    char * command = argv[1];
    char * filename = argv[2];
    int k = -1;
    if (argc == 4)
        k = atoi(argv[3]);
    double n;
    int i;
    int j;
    int numpoints=0;
    char c;
    double ** jacboi_mat;
    struct vector *head_vec;
    struct vector *curr_vec;
    struct cord *head_cord;
    struct cord *curr_cord;

    if(argc < 2){
        printf("invalid arguments");
        return -1;
    }

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
    if(strcmp(command, "jacobi") == 0){
        curr_vec = head_vec;
        jacboi_mat = calloc(numpoints, sizeof(double *));
        for(i = 0; i < numpoints; i ++)
        {
            jacboi_mat[i] = calloc(numpoints, sizeof(double));
            for(j=0; j < numpoints; j++){
                jacboi_mat[i][j] = curr_vec->cords->value;
                curr_vec->cords = curr_vec->cords->next;
            }
            curr_vec = curr_vec->next;
        }
    }



    fclose(file);
    if (strcmp(command, "spk") == 0)
        spk(head_vec, numpoints, k);
    else if (strcmp(command, "wam") == 0)
        wam(head_vec, numpoints);
    else if (strcmp(command, "ddg") == 0)
        ddg(head_vec, numpoints);
    else if (strcmp(command, "gl") == 0)
        gl(head_vec, numpoints);
    else if (strcmp(command, "jacobi") == 0)
        jacobi(jacboi_mat, numpoints, 1, -1);
    else {
        printf("--- Unkonown Command ---");
        return -1;
    }
    return 0;
}

void pythonModule(char* file, char* command)
{
    char * args[3] = {"spkmeans", command, file};
    main(3, args);
}

void spkModule(char* file, int k)
{
    char kk[1];
    kk[0] = k + '0';
    char * args[4] = {"spkmeans", "spk", file, kk};
    main(3, args);
}
