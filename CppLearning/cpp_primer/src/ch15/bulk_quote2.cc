#include "bulk_quote2.h"

#include <cstddef>

using std::size_t;

double BulkQuote2::net_price(size_t cnt) const {
  if (cnt >= quantity) {
    return cnt * (1 - discount) * price;
  } else {
    return cnt * price;
  }
}
