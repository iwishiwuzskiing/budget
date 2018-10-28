/**
 * @class Python_interpreter
 * Wrapper class around the Python interpreter for the python C api
 */

#ifndef SO_PYTHON_INTERPRETER_H
#define SO_PYTHON_INTERPRETER_H

#include <string>
#include <Python.h>

namespace so
{
class Python_interpreter
{
public:
  Python_interpreter(const std::string python_program = "")
  {
    if(!python_program.empty())
    {
      size_t len;
      m_program_name = Py_DecodeLocale(python_program.c_str(), &len);
      Py_SetProgramName(m_program_name);
    }
    Py_Initialize();
    PySys_SetArgvEx(0, nullptr, 0);
  }

  ~Python_interpreter()
  {
    Py_Finalize();
    PyMem_RawFree(m_program_name);
  }

private:
  /**
   * @brief m_program_name The path to the python executable to invoke for
   * interpretation
   */
  wchar_t* m_program_name;
};
}

#endif
