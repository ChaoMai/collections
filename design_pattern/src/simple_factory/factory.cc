#include "factory.h"

#include <memory>
#include <string>

#include "product.h"
#include "concrete_product.h"
#include "concrete_product1.h"

using std::make_shared;
using std::shared_ptr;
using std::string;

shared_ptr<Product> Factory::createProduct(string name) {
  if (name == "1") {
    return make_shared<ConcreteProduct1>();
  }
  return make_shared<ConcreteProduct>();
}
