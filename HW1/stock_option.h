/*
Author:      Eric Gustin
Assignment   #1
Description  Header file for the StockOption class which is a derived 
             class from Stock and Security.
*/

#ifndef STOCK_OPTION_H
#define STOCK_OPTION_H

#include <string>

#include "stock.h"

class StockOption : public Stock
{
public:
 // crate a stock option with the given symbol
 StockOption(std::string the_symbol);

 // set the strike price per share
 void set_strike_price(double the_strike_price);

 // strike price per share
 double get_strike_price() const;

 // the net worth of the option
 double sell_value() const;

private:
 double strike_price; // price to sell per holding
};

#endif