#include <python/python_object.h>
#include <python/python_utils.h>
#include <python/python_function.h>
#include <sno/logger.h>

#include <google_sheets_importer.h>
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

std::vector<std::vector<std::string>> Get_transactions()
{
  try
  {
    std::string module_name = "account_info";
    so::Python_object acct_info = so::Python_utils::Import_module("account_info");
    so::Python_function<std::vector<std::vector<std::string> > >
        get_transactions(acct_info, "get_transactions");
    std::vector<std::vector<std::string>> transactions = get_transactions();
    Log_msg(Logger::Debug) << "Retrieved " << transactions.size() << " transactions";
    return transactions;
  } catch (std::exception& e)
  {
    Log_msg(Logger::Debug) << "Failed to get transactions: " << e.what();
  }
}

int main(int argc, char** argv)
{
  // Python initialization
  // Use the version of python from the budget virtualenv
  Py_SetProgramName(L"/home/shay/development/budget/budget_env/bin/python3");
  Py_Initialize();
  PySys_SetArgvEx(0, nullptr, 0);

  Google_sheets_importer importer;
  importer.Read_transactions();
//  Get_transactions();

  Py_Finalize();
  return 0;
}
