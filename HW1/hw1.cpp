 assert(s2.market_worth() == 204*76);
 assert(s2.sell_value() == (204 -175)*76);

 StockOption s3("AMZN");
 s3.set_share_value(1823);
 s3.set_holdings(500);
 s3.set_purchase_price(5.25);
 s3.set_strike_price(1828);
 assert(s3.get_share_value() == 1823);
 assert(s3.get_holdings() == 500);
 assert(s3.get_purchase_price() == 5.25);
 assert(s3.get_strike_price() == 1828);
 assert(s3.market_worth() == 1823*500);
 assert(s3.sell_value() == (1828-5.25)*500 - 1823*500);

 assert(should_sell(s2) == true);
 assert(should_sell(s3) == false);
}

bool should_sell(Stock& the_stock)
{
 return the_stock.sell_value() > 0;
}