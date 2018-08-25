
#include <python/python_object.h>
#include <python/python_function.h>
#include <python/python_utils.h>
#include <sno/logger.h>

#include <google_sheets_importer.h>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

std::vector<Transaction> Google_sheets_importer::read_transactions()
{
  std::vector<std::vector<std::string>> raw_transactions;
  try
  {
    std::string module_name = "account_info";
    so::Python_object acct_info = so::Python_utils::Import_module("account_info");
    so::Python_function<std::vector<std::vector<std::string> > >
        get_transactions(acct_info, "get_transactions");
    raw_transactions = get_transactions();
    Log_msg(Logger::Debug) << "Retrieved " << raw_transactions.size() << " transactions\n";
  } catch (std::exception& e)
  {
    Log_msg(Logger::Debug) << "Failed to get transactions: " << e.what();
    throw;
  }

  std::vector<Transaction> transactions;
  transactions.reserve(raw_transactions.size());
  for(size_t k = 0; k < raw_transactions.size(); k++)
  {
    transactions.push_back(Transaction(raw_transactions[k]));
  }

  Log_msg(Logger::Debug) << "Parsed " << transactions.size() << " transactions";
  return transactions;
}
