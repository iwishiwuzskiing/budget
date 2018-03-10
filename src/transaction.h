

#include <string>
#include <set>
#include <boost/date_time/gregorian/gregorian.hpp>

class Transaction
{
public:

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
