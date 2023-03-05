#include "libpython.h"
#include <iostream>

namespace NaiSys {

LibPython::LibPython()
{

}

LibPython::~LibPython()
{

}

void LibPython::execute_string([[maybe_unused]]const char *script)
{
    try {
        Py_Initialize();
        PyRun_SimpleString(script);
    } catch (...) {
        std::cout << "[PY_SCOPE]: Error running python script";
    }
}

}

