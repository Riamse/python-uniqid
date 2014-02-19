/*
 * Whether this file is subject to the PHP license is ambiguous, so until
 * I clarify things, I'll just leave this file here.
 */


#include <Python.h>
#include <time.h>

static PyObject *
uniqid_uniqid(PyObject *self, PyObject *args, PyObject *kwargs)
{
    const char *prefix = "";
#if defined(__CYGWIN__)
    int more_entropy = 1;
#else
    int more_entropy = 0;
#endif
    char *uniqid;
    int sec, usec;
    struct timeval tv;
    static char *kwlist[] = {"prefix", "more_entropy", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|sp", kwlist, &prefix, &more_entropy)) {
        return NULL;
    }

#if HAVE_USLEEP && !defined(WIN32)
    if (!more_entropy) {
#if defined(__CYGWIN__)
        PyErr_SetString(PyExc_TypeError, "You must use more_entropy under CYGWIN");
        return NULL;
#else
        usleep(1);
#endif
    }
#endif

    gettimeofday((struct timeval *) &tv, (struct timezone *) NULL);
    sec = (int) tv.tv_sec;
    usec = (int) (tv.tv_usec % 0x100000);

    /* The max value usec can have is 0xF423F, so we use only five hex
     * digits for usecs.
     */
    if (more_entropy) {
        PyObject *random, *lcg, *lcg_res;
        double actual_res;
        random = PyImport_ImportModule("random");
        lcg = PyObject_GetAttrString(random, "random");
        lcg_res = PyObject_CallObject(lcg, NULL);
        actual_res = PyFloat_AS_DOUBLE(lcg_res);
        asprintf(&uniqid, "%s%08x%05x%.8F", prefix, sec, usec, actual_res * 10);
    } else {
        asprintf(&uniqid, "%s%08x%05x", prefix, sec, usec);
    }

    return PyUnicode_DecodeUTF8(uniqid, strlen(uniqid), NULL);
}

PyDoc_STRVAR(docs,
"uniqid([prefix=''[, more_entropy=False]]) -> str\n\
Gets a prefixed unique identifier based on the current\n\
time in microseconds.\n\
\n\
prefix\n\
    Can be useful, for instance, if you generate identifiers\n\
    simultaneously on several hosts that might happen to generate\n\
    the identifier at the same microsecond.\n\
    With an empty prefix, the returned string will be 13 characters\n\
    long. If more_entropy is TRUE, it will be 23 characters.\n\
\n\
more_entropy\n\
    If set to TRUE, uniqid() will add additional entropy (using\n\
    the combined linear congruential generator) at the end of\n\
    the return value, which increases the likelihood that\n\
    the result will be unique.\
");

static PyMethodDef UniqidMethods[] = {
    {"uniqid", (PyCFunction) uniqid_uniqid,
     METH_VARARGS | METH_KEYWORDS,
     docs
    },
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef uniqidmodule = {
    PyModuleDef_HEAD_INIT,
    "uniqid",
    "Generate a unique ID, à la PHP",
    -1,
    UniqidMethods
};

PyMODINIT_FUNC
PyInit_uniqid(void)
{
    return PyModule_Create(&uniqidmodule);
}

