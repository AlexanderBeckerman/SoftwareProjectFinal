
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>

struct cord
{
    double value;
    struct cord *next;
};
struct vector
{
    struct vector *next;
    struct cord *cords;
};

typedef struct vector Vector;
typedef struct cord Cord;

double ** ddg(Vector *, int);
double ** wam(Vector *, int);
double ** gl(Vector *, int);
double ** jacobi(double **, int, int, int);
Vector * spk(Vector *, int, int);
void pythonModule(char*, char*);
double ** spkModule(char*, int);