#ifndef QUOTE_H_
#define QUOTE_H_

#include <iostream>
#include <string>

class Quote {
 public:
  Quote() { std::cout << "default construct Quote" << std::endl; }
  Quote(const std::string &book, double sales_price)
      : bookNo(book), price(sales_price) {
    std::cout << "construct Quote" << std::endl;
  }
  Quote(const Quote &q) : bookNo(q.bookNo), price(q.price) {
    std::cout << "copy Quote" << std::endl;
  }
  Quote(Quote &&) = default;
  Quote &operator=(const Quote &rhs) {
    bookNo = rhs.bookNo;
    price = rhs.price;
    std::cout << "copy assign Quote" << std::endl;
    return *this;
  }
  Quote &operator=(Quote &&) = default;
  virtual ~Quote() { std::cout << "destory Quote" << std::endl; }

  std::string isbn() const { return bookNo; }
  virtual double net_price(std::size_t n) const { return n * price; }
  virtual void debug() const;

 private:
  std::string bookNo;

 protected:
  double price = 0.0;
};

#endif /* ifndef QUOTE_H_ */
