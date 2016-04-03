#ifndef CONCRETE_PRODUCT_H_
#define CONCRETE_PRODUCT_H_

#include "product.h"

class ConcreteProduct : public Product {
 public:
  ConcreteProduct() = default;
  ~ConcreteProduct() = default;

  void use() override;
};

#endif /* ifndef CONCRETE_PRODUCT_H_ */
