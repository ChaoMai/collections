#ifndef FACTORY_H_
#define FACTORY_H_

#include <memory>

#include "product.h"

class Factory {
 public:
  Factory() = default;
  virtual ~Factory() = default;

  virtual std::shared_ptr<Product> factoryMethod() = 0;
};

#endif /* ifndef FACTORY_H_ */
