#ifndef BULD_QUOTE2_H_
#define BULD_QUOTE2_H_

#include <cstddef>
#include <iostream>

#include "disc_quote.h"

class BulkQuote2 : public DiscQuote {
 public:
  using DiscQuote::DiscQuote;
  // BulkQuote2() { std::cout << "default construct BulkQuote2" << std::endl; }
  // BulkQuote2(const BulkQuote2& b) : DiscQuote(b) {
  // std::cout << "copy BulkQuote2" << std::endl;
  // }
  BulkQuote2& operator=(const BulkQuote2& rhs) {
    DiscQuote::operator=(rhs);
    std::cout << "copy assign BulkQuote2" << std::endl;
    return *this;
  }
  ~BulkQuote2() override { std::cout << "destory BulkQuote2" << std::endl; }

  double net_price(std::size_t) const override;
};

#endif /* ifndef BULD_QUOTE2_H_ */
