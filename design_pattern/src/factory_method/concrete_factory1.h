#ifndef CONCRETE_FACTORY1_H_
#define CONCRETE_FACTORY1_H_

#include <memory>

#include "factory.h"
#include "product.h"

class ConcreteFactory1 : public Factory {
 public:
  ConcreteFactory1() = default;
  ~ConcreteFactory1() = default;

  std::shared_ptr<Product> factoryMethod() override;
};

#endif /* ifndef CONCRETE_FACTORY1_H_ */
