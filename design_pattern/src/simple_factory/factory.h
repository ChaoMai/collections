#ifndef FACTORY_H_
#define FACTORY_H_

#include <memory>
#include <string>

#include "product.h"

class Factory {
 public:
  Factory() = default;
  ~Factory() = default;

  static std::shared_ptr<Product> createProduct(std::string name = "0");
};

#endif /* ifndef FACTORY_H_ */
