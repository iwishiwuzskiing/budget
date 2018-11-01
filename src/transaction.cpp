#include <boost/algorithm/string.hpp>

#include <sno/logger.h>
#include <sno/so_exception.h>
#include <transaction.h>

////////////////////////////////////////////////////////////////////////////////

Transaction::Transaction(const std::vector<std::string> transaction)
  :
    m_id(),
    m_account(),
    m_description(),
    m_amount(0),
    m_date(),
    m_category(),
    m_tags()
{
  if(transaction.size() != 14)
  {
    so::Log_msg(so::Logger::Warning) << "Invalid transaction. Expected 14 fields but found " << transaction.size() << std::endl;
    throw so::Invalid_argument("Invalid transaction, wrong number of fields");
  }
  m_id = transaction[12];
  m_account = transaction[6];
  m_description = transaction[1];

  std::string amount_str = transaction[4];
  boost::erase_all(amount_str, "$");
  boost::erase_all(amount_str, "'");
  try
  {
    m_amount = std::stod(amount_str);
  }
  catch(std::invalid_argument)
  {
    so::Log_msg(so::Logger::Warning) << "Failed to read transaction: Invalid amount '"
                             << transaction[4] << std::endl;
    throw so::Invalid_argument("Invalid transaction amount: '" + transaction[4] + "'");
  }

  std::string date_str = transaction[0];
  boost::erase_all(date_str, "'");
  try
  {
    m_date = boost::gregorian::from_us_string(date_str);
  }
  catch(std::exception& e)  //TODO: what does this actually throw?
  {
    so::Log_msg(so::Logger::Warning) << "Failed to read transaction: Invalid date '"
                             << transaction[0] << "' - " << e.what() << std::endl;
    throw so::Invalid_argument("Invalid transaction date: '" + transaction[0] + "'");
  }

  m_category = transaction[5];
}

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
