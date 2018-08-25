

#include <string>
#include <set>
#include <boost/date_time/gregorian/gregorian.hpp>

class Transaction
{
public:
  /**
   * @brief Constructor, a new transaction from a string array describing the
   * transaction. The array must have 14 elements:
   * 0    Date (MM/DD/YYYY
   * 1    Description
   * 2    Short description
   * 3    Full description
   * 4    Amount
   * 5    Category
   * 6    Account
   * 7    Account #
   * 8    Institution
   * 9    Check number
   * 10   Month (starting day)
   * 11   Week  (starting day)
   * 12   Transaction ID
   * 13   Date Added
   * @param transaction Vector describing the transaction
   */
  Transaction(const std::vector<std::string> transaction);

protected:

private:
  /**
   * @brief m_id Unique identifier for this transaction
   */
  std::string m_id;

  /**
   * @brief m_account The account this transaction is associated with
   */
  std::string m_account;

  /**
   * @brief m_description Description of the transaction
   */
  std::string m_description;

  /**
   * @brief m_amount The amount of the transaction, dollars
   */
  double m_amount;

  /**
   * @brief m_date The date this transaction took place
   */
  boost::gregorian::date m_date;

  /**
   * @brief m_category The category for this transaction
   */
  std::string m_category;

  /**
   * @brief m_tags The tags associated with this transaction
   */
  std::set<std::string> m_tags;
};
