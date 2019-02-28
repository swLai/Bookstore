#ifndef QUOTE_H
#define QUOTE_H

#include <string>
#include <iostream>
#include <utility>

class Quote
{
    friend std::istream& operator>>(std::istream&, Quote&);
    friend std::ostream& operator<<(std::ostream&, const Quote&);

public:
    Quote() = default;
    Quote(const std::string &book, double sales_price)
        : book_no(book), price(sales_price) {}
    Quote(const Quote&) = default;
    Quote(Quote&&) = default;
    Quote& operator=(const Quote&) = default;
    Quote& operator=(Quote&&) = default;
    virtual ~Quote() = default;

    std::string isbn() const
    {
        return book_no;
    }
    virtual double net_price(std::size_t n) const
    {
        return n * price;
    }
    virtual Quote* clone() const &
    {
        return new Quote(*this);
    }
    virtual Quote* clone() &&
    {
        return new Quote(std::move(*this));
    }

protected: // can be accessed by descendants
    double price = 0.0;

private:
    std::string book_no;
};

class Disc_quote : public Quote
{
public:
    Disc_quote() = default;
    Disc_quote(const std::string book, double price, std::size_t qty, double disc)
        : Quote(book, price), quantity(qty), discount(disc) {}

    double net_price(std::size_t) const = 0;
    std::pair<size_t, double> discount_policy() const
    {
        return {quantity, discount};
    }

protected:
    std::size_t quantity = 0;
    double discount = 0.0;
};

class Bulk_quote : public Disc_quote
{
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string &book, double price, std::size_t qty, double disc)
        : Disc_quote(book, price, qty, disc) {}

    double net_price(std::size_t) const override;

    Bulk_quote* clone() const &
    {
        return new Bulk_quote(*this);
    }
    Bulk_quote* clone() &&
    {
        return new Bulk_quote(std::move(*this));
    }
};

double print_total(std::ostream &, const Quote&, std::size_t);

#endif // QUOTE_H
