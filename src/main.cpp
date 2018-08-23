#include <python/python_object.h>
#include <python/python_utils.h>
#include <python/python_function.h>
#include <sno/logger.h>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// Globals
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Function Definitions
////////////////////////////////////////////////////////////////////////////////

void Get_transactions()
{
  try
  {
    std::string module_name = "account_info";
    so::Python_object acct_info = so::Python_utils::Import_module("account_info");
    so::Python_function<std::vector<std::vector<std::string> > >
        get_transactions(acct_info, "get_transactions");
    std::vector<std::vector<std::string>> transactions = get_transactions();
    Log_msg(Logger<>::Debug) << "Retrieved " << transactions.size() << " transactions";
  } catch (std::exception& e)
  {
    Log_msg(Logger<>::Debug) << "Failed to get transactions: " << e.what();
  }

}

int main(int argc, char** argv)
{
  PyObject *pName, *pModule, *pDict, *pFunc;
  PyObject *pArgs, *pValue;
  int i;

  if (argc < 3) {
    fprintf(stderr,"Usage: call pythonfile funcname [args]\n");
    return 1;
  }

  Py_SetProgramName(L"/home/shay/development/budget/budget_env/bin/python3");
  Py_Initialize();
  PySys_SetArgvEx(0, nullptr, 0);


  Get_transactions();
  return 0;

  pName = PyUnicode_DecodeFSDefault(argv[1]);
  /* Error checking of pName left out */

  pModule = PyImport_ImportModule(argv[1]);//pName);
  Py_DECREF(pName);

  if (pModule != NULL)
  {
    pFunc = PyObject_GetAttrString(pModule, argv[2]);
    /* pFunc is a new reference */

    if (pFunc && PyCallable_Check(pFunc))
    {
      pArgs = PyTuple_New( (argc - 3) > 0 ? argc - 3 : 0);
      for (i = 0; i < argc - 3; ++i)
      {
        pValue = PyLong_FromLong(atoi(argv[i + 3]));
        if (!pValue) {
          Py_DECREF(pArgs);
          Py_DECREF(pModule);
          fprintf(stderr, "Cannot convert argument\n");
          return 1;
        }
        /* pValue reference stolen here: */
        PyTuple_SetItem(pArgs, i, pValue);
      }
      pValue = PyObject_CallObject(pFunc, pArgs);
      Py_DECREF(pArgs);
      if (pValue != NULL)
      {
        Py_ssize_t num_transactions = PyList_Size(pValue);

        printf("Retrieved %ld transactions\n", num_transactions);
        Py_DECREF(pValue);
      }
      else
      {
        Py_DECREF(pFunc);
        Py_DECREF(pModule);
        PyErr_Print();
        fprintf(stderr,"Call failed\n");
        return 1;
      }
    }
    else
    {
      if (PyErr_Occurred())
        PyErr_Print();
      fprintf(stderr, "Cannot find function \"%s\"\n", argv[2]);
    }
    Py_XDECREF(pFunc);
    Py_DECREF(pModule);
  }
  else
  {
    PyErr_Print();
    fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
    return 1;
  }
  std::cout << std::endl;
  std::cerr << std::endl;

  Py_Finalize();
  return 0;
}
