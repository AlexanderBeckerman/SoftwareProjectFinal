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
    double ** points;
    if(!PyArg_ParseTuple(args, "si", &filename, &k)) {
        return NULL;
    }

    points = spkModule(filename, k);
    points--;
    numpoints = points[0][0];
    dim = points[0][1];
    points++;

    listVectors = PyList_New(numpoints);
    for (i = 0; i != numpoints; ++i) {
        PyList_SET_ITEM(listVectors, i, PyList_New(dim));
        for (j = 0; j != dim; ++j) {
            PyList_SET_ITEM(PyList_GetItem(listVectors, i), j, PyFloat_FromDouble(points[i][j]));
        }
    }

    return listVectors;
}

static PyObject* ddg_module(PyObject *self, PyObject *args)
{
    char* filename  = getFile(self, args);
    pythonModule(filename, "ddg");
    Py_RETURN_NONE;
}

static PyObject* wam_module(PyObject *self, PyObject *args)
{
    char* filename  = getFile(self, args);
    pythonModule(filename, "wam");
    Py_RETURN_NONE;
}
static PyObject* jacobi_module(PyObject *self, PyObject *args)
{
    char* filename  = getFile(self, args);
    pythonModule(filename, "jacobi");
    Py_RETURN_NONE;
}

static PyObject* gl_module(PyObject *self, PyObject *args)
{
    char* filename  = getFile(self, args);
    pythonModule(filename, "gl");
    Py_RETURN_NONE;
}

static PyObject* kmeans_module(PyObject *self, PyObject *args)
{
    int iter;
    PyObject* centList;
    PyObject* pointList;
    PyObject* item;
    double num;
    int n;
    int m;
    int k;
    int i;
    int j;

    if(!PyArg_ParseTuple(args, "iiOO", &iter,&m, &centList, &pointList)) {
        return NULL;
    }

    n = PyObject_Length(pointList);
    k = PyObject_Length(centList);

    if (n <= 0 || k <= 0 || m <= 0) {
        return NULL;
    }

    Vector *points = malloc(sizeof (Vector));
    Vector **centroids = calloc(k, sizeof (Vector));
    Vector *pointsIter = points;
    for (i = 0; i < n; i++) {
        pointsIter->cords = malloc(sizeof (Cord));
        pointsIter->next = NULL;
        struct cord *cordsIter = pointsIter->cords;
        for (j = 0; j < m; j++)
        {
            item = PyList_GetItem(PyList_GetItem(pointList, i), j);
            num = PyFloat_AsDouble(item);
            cordsIter->next = NULL;
            cordsIter->value = num;
            if (j != m - 1) {
                cordsIter->next = malloc(sizeof (Cord));
                cordsIter = cordsIter->next;
            }
        }

        if (i != n - 1) {
            pointsIter->next = malloc(sizeof(Vector));
            pointsIter = pointsIter->next;
        }

    }

    for (i = 0; i < k; i++) {
        centroids[i] = malloc(sizeof (Vector));
        centroids[i]->next = NULL;
        centroids[i]->cords = malloc(sizeof (Cord));;
        struct cord *cordsIter = centroids[i]->cords;
        for (j = 0; j < m; j++)
        {
            item = PyList_GetItem(PyList_GetItem(centList, i), j);
            num = PyFloat_AsDouble(item);
            cordsIter->next = NULL;
            cordsIter->value = num;
            if (j != m - 1) {
                cordsIter->next = malloc(sizeof (Cord));
                cordsIter = cordsIter->next;
            }
        }
    }
    kmeans(iter, k, centroids, points);
    Py_RETURN_NONE;
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