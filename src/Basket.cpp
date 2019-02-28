#include "../include/Basket.h"
#include "../include/Book.h"

#include <iostream>
using namespace std;

double Basket::total_receipt(ostream &os) const
{
    double sum = 0.0;

    for (auto iter = books.cbegin(); iter != books.cend(); iter = books.upper_bound(*iter))
        sum += print_total(os, **iter, books.count(*iter));

    return sum;
}
