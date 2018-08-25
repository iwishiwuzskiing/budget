#include <transaction_importer.h>

class Google_sheets_importer : public Transaction_importer
{
public:

private:

  /**
   * @brief Read transactions from google sheets
   * @return Vector of transaction information
   */
  std::vector<Transaction> read_transactions();

};
