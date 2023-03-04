#ifndef NAISYS_LIB_PYTHON_H
#define NAISYS_LIB_PYTHON_H

#define PY_SSIZE_T_CLEAN
#include <Python.h>

namespace NaiSys {

class LibPython
{
public:
    LibPython();
    ~LibPython();

public:
    static void execute_string(const char* script);
};

}

#endif
