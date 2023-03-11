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
        wchar_t *program = Py_DecodeLocale("./python", NULL);
        wchar_t *pypath =
                Py_DecodeLocale("./pythonlib", NULL);
        if (program == NULL) {
                fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
                exit(1);
            }
        Py_SetProgramName(program);
        Py_SetPythonHome(pypath);

        if(!Py_IsInitialized()) {
            Py_Initialize();
        }

        fprintf(stdout, "%s", (const char *)Py_GetPath());
        PyRun_SimpleString(script);
    } catch (...) {
        std::cout << "[PY_SCOPE]: Error running python script";
    }
}

}

