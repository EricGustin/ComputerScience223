/* 
Author:      Eric Gustin
Assignment   #1
Description  Derived class of the Stock class, which is a subclass of the
             Security parent class. Introduces functionality to sell a stock,
             as well as a strike price.
*/

#include <iostream>

#include "stock_option.h"

StockOption::StockOption(std::string the_symbol) : Stock(the_symbol), strike_price(0)
{
}

void StockOption::set_strike_price(double the_strike_price)
{
 if (the_strike_price >= 0)
 {
  strike_price = the_strike_price;
 }
}

double StockOption::get_strike_price() const
{
 return strike_price;
}

double StockOption::sell_value() const
{
 return (get_strike_price() - get_purchase_price()) * get_holdings() - get_share_value() * get_holdings();
}