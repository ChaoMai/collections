#ifndef LIMIT_QUOTE_H_
#define LIMIT_QUOTE_H_

#include <string>

#include "quote.h"

class LimitQuote : public Quote {
 public:
  LimitQuote() = default;
  LimitQuote(const std::string&, double, std::size_t, double);
  double net_price(std::size_t) const override;

 private:
  std::size_t max_qty = 0;
  double discount = 0.0;
};

#endif /* ifndef LIMIT_QUOTE_H_ */
