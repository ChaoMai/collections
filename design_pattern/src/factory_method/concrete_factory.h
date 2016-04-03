#ifndef CONCRETE_FACTORY_H_
#define CONCRETE_FACTORY_H_

#include <memory>

#include "factory.h"
#include "product.h"

class ConcreteFactory : public Factory {
 public:
  ConcreteFactory() = default;
  ~ConcreteFactory() = default;

  std::shared_ptr<Product> factoryMethod() override;
};

#endif /* ifndef CONCRETE_FACTORY_H_ */
