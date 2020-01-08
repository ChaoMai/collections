#include "bulk_quote1.h"

#include <cstddef>

using std::size_t;

double BulkQuote1::net_price(size_t cnt) const {
  if (cnt >= quantity) {
    return cnt * (1 - discount) * price;
  } else {
    return cnt * price;
  }
}
