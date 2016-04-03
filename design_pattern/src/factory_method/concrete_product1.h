#ifndef CONCRETE_PRODUCT1_H_
#define CONCRETE_PRODUCT1_H_

#include "product.h"

class ConcreteProduct1 : public Product {
 public:
  ConcreteProduct1() = default;
  ~ConcreteProduct1() = default;

  void use() override;
};

#endif /* ifndef CONCRETE_PRODUCT1_H_ */
