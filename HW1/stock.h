/*
Author:      Eric Gustin
Assignment   #1
Description  Header file for the Stock class which is a subclass of Security,
             and a parent for the StockOption class.
*/

#ifndef STOCK_H
#define STOCK_H

#include "security.h"

class Stock : public Security
{
public:
 // create a stock with the given company symbol
 Stock(std::string the_symbol);

 // set the purchase price of the holdings
 void set_purchase_price(double the_purchase_price);

 // purchase price
 double get_purchase_price() const ;

 // compute the net worth of the stock holdings
 virtual double sell_value() const ;

private:
 double purchase_price; // price per holding
};

#endif
