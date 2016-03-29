#include "basket.h"

#include <iostream>

using std::ostream;
using std::endl;

void Basket::add_item(const Quote &) {}

void Basket::add_item(Quote &&) {}

double Basket::total_receipt(ostream &os) const {
  double sum = 0.0;
  for (auto iter = items.cbegin(); iter != items.cend();
       iter = items.upper_bound(*iter)) {
    sum += print_total(os, **iter, items.count(*iter));
  }
}

double Basket::print_total(ostream &os, const Quote &item, size_t n) const {
  double ret = item.net_price(n);
  os << "ISBN: " << item.isbn() << "# sold: " << n << " total due: " << ret
     << endl;
  return ret;
}
