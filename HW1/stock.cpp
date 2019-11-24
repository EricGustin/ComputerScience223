/* 
Author:      Eric Gustin
Assignment   #1
Description  Subclass of the Security parent class. This subclass introduces
a purchase price of a stock that is owned by someone.
*/

#include <iostream>

#include "stock.h"

Stock::Stock(std::string the_symbol) : Security(the_symbol), purchase_price(0)
{
}

 void Stock::set_purchase_price(double the_purchase_price)
 {
  if (the_purchase_price >= 0)
  {
   purchase_price = the_purchase_price;
  }
 }

 double Stock::get_purchase_price() const
 {
  return purchase_price;
 }

 double Stock::sell_value() const
 {
  return (get_share_value() - get_purchase_price()) * get_holdings();
 }
