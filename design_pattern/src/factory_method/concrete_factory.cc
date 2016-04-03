#include "concrete_factory.h"

#include <memory>

#include "product.h"
#include "concrete_product.h"

using std::make_shared;
using std::shared_ptr;

shared_ptr<Product> ConcreteFactory::factoryMethod() {
  return make_shared<ConcreteProduct>();
}
