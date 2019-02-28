#ifndef QUOTE_H
#define QUOTE_H

#include <string>
#include <iostream>
#include <utility>

class Book
{
    friend std::istream& operator>>(std::istream&, Book&);
    friend std::ostream& operator<<(std::ostream&, const Book&);

public:
    Book() = default;
    Book(const std::string &book, double sales_price)
        : book_no(book), price(sales_price) {}
    Book(const Book&) = default;
    Book(Book&&) = default;
    Book& operator=(const Book&) = default;
    Book& operator=(Book&&) = default;
    virtual ~Book() = default;

    std::string isbn() const
    {
        return book_no;
    }
    virtual double net_price(std::size_t n) const
    {
        return n * price;
    }
    virtual Book* clone() const &
    {
        return new Book(*this);
    }
    virtual Book* clone() &&
    {
        return new Book(std::move(*this));
    }

protected: // can be accessed by descendants
    double price = 0.0;

private:
    std::string book_no;
};

class Disc_book : public Book
{
public:
    Disc_book() = default;
    Disc_book(const std::string book, double price, std::size_t qty, double disc)
        : Book(book, price), quantity(qty), discount(disc) {}

    double net_price(std::size_t) const = 0;
    std::pair<size_t, double> discount_policy() const
    {
        return {quantity, discount};
    }

protected:
    std::size_t quantity = 0;
    double discount = 0.0;
};

class A_book : public Disc_book
{
public:
    A_book() = default;
    A_book(const std::string &book, double price, std::size_t qty, double disc)
        : Disc_book(book, price, qty, disc) {}

    double net_price(std::size_t) const override;

    A_book* clone() const &
    {
        return new A_book(*this);
    }
    A_book* clone() &&
    {
        return new A_book(std::move(*this));
    }
};

double print_total(std::ostream &, const Book&, std::size_t);

#endif // QUOTE_H
