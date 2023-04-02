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

void spk_module(PyObject *self, PyObject *args)
{
    char* filename;
    int k;
    if(!PyArg_ParseTuple(args, "si", &filename, &k)) {
        return NULL;
    }

    pythonModule(filename, "spk");
}

void ddg_module(PyObject *self, PyObject *args)
{
    char* filename  = getFile(self, args);
    pythonModule(filename, "ddg");
}

void wam_module(PyObject *self, PyObject *args)
{
    char* filename  = getFile(self, args);
    pythonModule(filename, "wam");
}
void jacobi_module(PyObject *self, PyObject *args)
{
    char* filename  = getFile(self, args);
    pythonModule(filename, "jacobi");
}

void gl_module(PyObject *self, PyObject *args)
{
    char* filename  = getFile(self, args);
    pythonModule(filename, "gl");
}

static PyMethodDef spkmeansMethods[] = {
        {"spk", spk_module, METH_VARARGS, "The spk algorithm"},
        {"ddg", ddg_module, METH_VARARGS, "The ddg algorithm"},
        {"gl", gl_module, METH_VARARGS, "The gl algorithm"},
        {"wam", wam_module, METH_VARARGS, "The wam algorithm"},
        {"jacobi", jacobi_module, METH_VARARGS, "The jacobi algorithm"},
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