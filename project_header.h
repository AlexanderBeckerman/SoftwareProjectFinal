
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

int ddg(int, Vector *);