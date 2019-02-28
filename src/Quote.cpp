#include "../include/Quote.h"

#include <iostream>
using namespace std;

double Bulk_quote::net_price(std::size_t cnt) const
{
    if (cnt >= quantity)
        return cnt * (1 - discount) * price;
    else
        return cnt * price;
}

double print_total(ostream &os, const Quote &item, size_t n)
{
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn()
       << ", # sold: " << n
       << ", total due: " << ret
       << endl;
    return ret;
}
