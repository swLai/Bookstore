#include "../include/Book.h"

#include <iostream>
using namespace std;

double A_book::net_price(std::size_t cnt) const
{
    if (cnt >= quantity)
        return cnt * (1 - discount) * price;
    else
        return cnt * price;
}

double print_total(ostream &os, const Book &book, size_t n)
{
    double ret = book.net_price(n);
    os << "ISBN: " << book.isbn()
       << ", # sold: " << n
       << ", total due: " << ret
       << endl;
    return ret;
}
