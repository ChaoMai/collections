#ifndef BASKET_H_
#define BASKET_H_

#include <iostream>
#include <memory>
#include <set>
#include "quote.h"

class Basket {
 public:
  void add_item(std::shared_ptr<Quote> &sale) { items.insert(sale); }
  void add_item(const Quote &);
  void add_item(Quote &&);
  double total_receipt(std::ostream &) const;

 private:
  static bool compare(const std::shared_ptr<Quote> &lhs,
                      const std::shared_ptr<Quote> &rhs) {
    return lhs->isbn() < rhs->isbn();
  }
  double print_total(std::ostream &os, const Quote &item, std::size_t n) const;
  std::multiset<std::shared_ptr<Quote>, decltype(compare) *> items{compare};
};

#endif /* ifndef BASKET_H_ */
