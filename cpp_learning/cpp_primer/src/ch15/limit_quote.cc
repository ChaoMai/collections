#include "limit_quote.h"

LimitQuote::LimitQuote(const std::string& book, double p, std::size_t qty,
                       double disc)
    : Quote(book, p), max_qty(qty), discount(disc) {}

double LimitQuote::net_price(std::size_t cnt) const {
  if (cnt <= max_qty) {
    return cnt * (1 - discount) * price;
  } else {
    return cnt * price;
  }
}
