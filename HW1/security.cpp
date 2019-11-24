/*
Author:      Eric Gustin. Worked with Brian Stueber
Assignment   #1
Description  Implementation of the parent class Security. Allows for the
             to create an object that can consist of the stock ticket symbol,
             the share value of the asset, and the number of holdings in the
             security.
 */

#include <iostream>

#include "security.h"

Security::Security(std::string the_symbol) : symbol(the_symbol), share_value(0),
 holdings(0)
{
}

std::string Security::get_symbol()
{
 return symbol;
}

void Security::set_share_value(double current_share_value)
{
 if (current_share_value >= 0)
 {
  share_value = current_share_value;
 }
}

 double Security::get_share_value() const
 {
  return share_value;
 }

 void Security::set_holdings(int number_of_holdings)
 {
  if (number_of_holdings >= 0)
  {
   holdings = number_of_holdings;
  }
 }

 int Security::get_holdings() const
 {
  return holdings;
 }

 double Security::market_worth() const
 {
  return holdings * share_value;
 }