

#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>

class Transaction
{
public:

protected:

private:
  /**
   * @brief m_account The account this transaction is associated with
   */
  std::string m_account;

  /**
   * @brief m_amount The amount of the transaction, dollars
   */
  double m_amount;

  /**
   * @brief m_date The date this transaction took place
   */
  boost::gregorian::date m_date;
};
