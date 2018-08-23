#!/home/shay/development/budget/budget_env/bin/python
import account_info

values = account_info.get_transactions()

if not values:
  print('No data found.')
else:
  print('Date, Amount:')
  for row in values:
    # Print columns A and E, which correspond to indices 0 and 4.
    print('%s, %s' % (row[0], row[4]))
    
