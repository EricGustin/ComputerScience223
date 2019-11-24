
 /*
Author:      Eric Gustin
Assignment   #1
Description  Header file for the SSecurity class which is a parent class
             for the classes Stock and StockOption.
*/

#ifndef SECURITY_H
#define SECURITY_H

#include <string>

class Security
{
public:
 // create a security with the given symbol
 Security(std::string the_symbol);

 //company symbol
 std::string get_symbol();

 //update the current share value
 void set_share_value(double current_share_value);

 // current share value
 double get_share_value() const;

 //update the number
 void set_holdings(int number_of_holdings);

 // current number of holdings
 int get_holdings() const;

 //total current value of all holdings
 double market_worth() const;

private:
 std::string symbol;                   // security identifier
 double share_value;               // each share's current market value
 int holdings;                     // number of total shares of security held
};

#endif