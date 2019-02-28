#ifndef BASKET_H
#define BASKET_H

#include <memory>
#include <set>

#include "./Book.h"
class Book;

class Basket
{
public:
    void add_item(const Book &sale)
    {
        items.insert(std::shared_ptr<Book>(sale.clone()));
    }
    void add_item(Book &&sale)
    {
        items.insert(std::shared_ptr<Book>(std::move(sale).clone()));
    }

    double total_receipt(std::ostream &) const;

private:
    static bool compare(const std::shared_ptr<Book> &lhs,
                        const std::shared_ptr<Book> &rhs)
    {
        return lhs->isbn() < rhs->isbn();
    }
    std::multiset<std::shared_ptr<Book>, decltype(compare)*> items{compare};
};

#endif // BASKET_H
