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
   * @brief Get any new transactions for the provided account
   * @param[out] db Database to ad transactions to
   */
  void Add_transactions(Transaction_db& db);

private:
  /**
   * @brief Get any new transactions for the provided account
   * @param[out] acct Account to get transactions for
   */
  virtual void add_transactions() = 0;
private:
};
