#ifndef DISC_QUOTE_H_
#define DISC_QUOTE_H_

#include <cstddef>
#include <iostream>
#include <string>
#include <utility>

#include "quote.h"

class DiscQuote : public Quote {
 public:
  DiscQuote() { std::cout << "default construct DiscQuote" << std::endl; }
  DiscQuote(const std::string& book, double price, std::size_t qty, double disc)
      : Quote(book, price), quantity(qty), discount(disc) {
    std::cout << "construct DiscQuote" << std::endl;
  }
  DiscQuote(const DiscQuote& d)
      : Quote(d), quantity(d.quantity), discount(d.discount) {
    std::cout << "copy DiscQuote" << std::endl;
  }
  DiscQuote& operator=(const DiscQuote& rhs) {
    Quote::operator=(rhs);
    quantity = rhs.quantity;
    discount = rhs.discount;
    std::cout << "copy assign DiscQuote" << std::endl;
    return *this;
  }
  ~DiscQuote() override { std::cout << "destory DiscQuote" << std::endl; }

  std::pair<std::size_t, double> discount_policy() const {
    return {quantity, discount};
  }
  double net_price(std::size_t) const = 0;

 protected:
  std::size_t quantity = 0;
  double discount = 0.0;
};

#endif /* ifndef DISC_QUOTE_H_ */
