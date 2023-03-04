#include "libpython.h"

namespace NaiSys {

LibPython::LibPython()
{

}

LibPython::~LibPython()
{

}

void LibPython::execute_string([[maybe_unused]]const char *script)
{
    Py_Initialize();
    PyRun_SimpleString(script);
}

}

