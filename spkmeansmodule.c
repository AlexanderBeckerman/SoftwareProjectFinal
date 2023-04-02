#include "spkmeans.h"
# define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static char* getFile(PyObject *self, PyObject *args)
{
    char* filename;

    if(!PyArg_ParseTuple(args, "s", &filename)) {
        return NULL;
    }

    return filename;
}

static PyObject* spk_module(PyObject *self, PyObject *args)
{
    char* filename;
    int k, i, j, numpoints, dim;
    PyObject *listVectors;
    PyObject *vector;
    double ** points;
    if(!PyArg_ParseTuple(args, "si", &filename, &k)) {
        return;
    }

    points = spkModule(filename, k);

    numpoints = sizeof(points) / sizeof(points[0]);
    dim = sizeof(points[0]) / sizeof(points[0][0]);

    listVectors = PyList_New(numpoints);
    for (i = 0; i != numpoints; ++i) {
        PyList_SET_ITEM(listVectors, i, PyList_New(dim));
        for (j = 0; j != dim; ++j) {
            PyList_SET_ITEM(PyList_GetItem(listVectors, i), j, PyFloat_AsDouble(points[i][j]));
        }
    }

    return listVectors;
}

static void ddg_module(PyObject *self, PyObject *args)
{
    char* filename  = getFile(self, args);
    pythonModule(filename, "ddg");
}

static void wam_module(PyObject *self, PyObject *args)
{
    char* filename  = getFile(self, args);
    pythonModule(filename, "wam");
}
static void jacobi_module(PyObject *self, PyObject *args)
{
    char* filename  = getFile(self, args);
    pythonModule(filename, "jacobi");
}

static void gl_module(PyObject *self, PyObject *args)
{
    char* filename  = getFile(self, args);
    pythonModule(filename, "gl");
}

static void kmeans_module(PyObject *self, PyObject *args)
{
    int iter;
    double epsilon;
    PyObject* centList;
    PyObject* pointList;
    PyObject* item;
    double num;
    int n;
    int m;
    int k;
    int i;
    int j;

    if(!PyArg_ParseTuple(args, "idiOO", &iter, &epsilon,&m, &centList, &pointList)) {
        return NULL;
    }

    n = PyObject_Length(pointList);
    k = PyObject_Length(centList);

    if (n <= 0 || k <= 0 || m <= 0) {
        return NULL;
    }

    struct vector *points = malloc(sizeof (struct vector));
    struct vector **centroids = calloc(k, sizeof (struct vector));
    struct vector *pointsIter = points;
    for (i = 0; i < n; i++) {
        pointsIter->cords = malloc(sizeof (struct cord));
        pointsIter->next = NULL;
        struct cord *cordsIter = pointsIter->cords;
        for (j = 0; j < m; j++)
        {
            item = PyList_GetItem(PyList_GetItem(pointList, i), j);
            num = PyFloat_AsDouble(item);
            cordsIter->next = NULL;
            cordsIter->value = num;
            if (j != m - 1) {
                cordsIter->next = malloc(sizeof (struct cord));
                cordsIter = cordsIter->next;
            }
        }

        if (i != n - 1) {
            pointsIter->next = malloc(sizeof(struct vector));
            pointsIter = pointsIter->next;
        }

    }

    for (i = 0; i < k; i++) {
        centroids[i] = malloc(sizeof (struct vector));
        centroids[i]->next = NULL;
        centroids[i]->cords = malloc(sizeof (struct cord));;
        struct cord *cordsIter = centroids[i]->cords;
        for (j = 0; j < m; j++)
        {
            item = PyList_GetItem(PyList_GetItem(centList, i), j);
            num = PyFloat_AsDouble(item);
            cordsIter->next = NULL;
            cordsIter->value = num;
            if (j != m - 1) {
                cordsIter->next = malloc(sizeof (struct cord));
                cordsIter = cordsIter->next;
            }
        }
    }
    kmeans(iter, epsilon, k, centroids, points);
}

static PyMethodDef spkmeansMethods[] = {
        {"spk", spk_module, METH_VARARGS, "The spk algorithm"},
        {"ddg", ddg_module, METH_VARARGS, "The ddg algorithm"},
        {"gl", gl_module, METH_VARARGS, "The gl algorithm"},
        {"wam", wam_module, METH_VARARGS, "The wam algorithm"},
        {"jacobi", jacobi_module, METH_VARARGS, "The jacobi algorithm"},
        {"kmeans", kmeans_module, METH_VARARGS, "The kmeans algorithm"},
        {NULL, NULL, 0, NULL}
};

static struct PyModuleDef SPK_Means_Module = {
        PyModuleDef_HEAD_INIT,
        "spkmeans",     // name of module exposed to Python
        "spkmeans algorithm", // module documentation
        -1,
        spkmeansMethods
};

PyMODINIT_FUNC PyInit_spkmeans(void) {
    return PyModule_Create(&SPK_Means_Module);
}