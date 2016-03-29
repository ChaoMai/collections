#ifndef BULK_QUOTE1_H_
#define BULK_QUOTE1_H_

#include <cstddef>
#include <iostream>

#include "disc_quote.h"

class BulkQuote1 : public DiscQuote {
 public:
  BulkQuote1() { std::cout << "default construct BulkQuote1" << std::endl; }
  BulkQuote1(const std::string& book, double price, std::size_t qty,
             double disc)
      : DiscQuote(book, price, qty, disc) {
    std::cout << "construct BulkQuote1" << std::endl;
  }
  BulkQuote1(const BulkQuote1& b) : DiscQuote(b) {
    std::cout << "copy BulkQuote1" << std::endl;
  }
  BulkQuote1& operator=(const BulkQuote1& rhs) {
    DiscQuote::operator=(rhs);
    std::cout << "copy assign BulkQuote1" << std::endl;
    return *this;
  }
  ~BulkQuote1() override { std::cout << "destory BulkQuote1" << std::endl; }

  double net_price(std::size_t) const override;
};

#endif /* ifndef BULK_QUOTE1_H_ */
