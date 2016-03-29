#ifndef BULK_QUOTE_H_
#define BULK_QUOTE_H_

#include <string>

#include "quote.h"

class BulkQuote : public Quote {
 public:
  BulkQuote() = default;
  BulkQuote(const std::string&, double, std::size_t, double);
  double net_price(std::size_t) const override;
  void debug() const override;

 private:
  std::size_t min_qty = 0;
  double discount = 0.0;
};

#endif /* ifndef BULK_QUOTE_H_ */
