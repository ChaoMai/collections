#ifndef LIMIT_QUOTE1_H_
#define LIMIT_QUOTE1_H_

#include <cstddef>

#include "disc_quote.h"

class LimitQuote1 : DiscQuote {
 public:
  LimitQuote1() = default;
  LimitQuote1(const std::string& book, double price, std::size_t qty,
              double disc)
      : DiscQuote(book, price, qty, disc) {}
  double net_price(std::size_t) const override;
};

#endif /* ifndef LIMIT_QUOTE1_H_ */
