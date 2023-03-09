#include "libpython.h"
#include <iostream>

namespace NaiSys {

LibPython::LibPython()
{

}

LibPython::~LibPython()
{

}

//For some reason [[maybe_unused]] causes parse errors in MacOS
void LibPython::execute_string(__attribute__((unused)) const char *script)
{
    try {
        Py_Initialize();
        PyRun_SimpleString(script);
    } catch (...) {
        std::cout << "[PY_SCOPE]: Error running python script";
    }
}

}

