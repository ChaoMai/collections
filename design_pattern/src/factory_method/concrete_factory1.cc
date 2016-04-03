#include "concrete_factory1.h"

#include <memory>

#include "product.h"
#include "concrete_product1.h"

using std::make_shared;
using std::shared_ptr;

shared_ptr<Product> ConcreteFactory1::factoryMethod() {
  return make_shared<ConcreteProduct1>();
}
