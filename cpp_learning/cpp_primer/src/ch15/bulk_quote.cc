#include "bulk_quote.h"

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

BulkQuote::BulkQuote(const string& book, double p, size_t qty, double disc)
    : Quote(book, p), min_qty(qty), discount(disc) {}

double BulkQuote::net_price(size_t cnt) const {
  if (cnt >= min_qty) {
    return cnt * (1 - discount) * price;
  } else {
    return cnt * price;
  }
}

void BulkQuote::debug() const {
  Quote::debug();
  cout << "min_qty: " << min_qty << endl << "discount: " << discount << endl;
}
