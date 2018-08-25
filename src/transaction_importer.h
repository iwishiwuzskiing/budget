#include <transaction_db.h>
#include <account.h>

class Transaction_importer
{
public:
  /**
   * @brief Destructor
   */
  virtual ~Transaction_importer(){}

  /**
   * @brief Read transactions
   * @return Vector of transaction information
   */
  std::vector<Transaction> Read_transactions()
  {
    return read_transactions();
  }

  /**
   * @brief Get any new transactions for the provided account
   * @param[out] db Database to add transactions to
   */
//  void Add_transactions(Transaction_db& db);

private:
  /**
   * @brief Get a list of transactions
   * @return List of transactions
   */
  virtual std::vector<Transaction> read_transactions() = 0;
};
