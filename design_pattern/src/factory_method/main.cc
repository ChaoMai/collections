#include <memory>

#include "concrete_factory.h"
#include "product.h"

using std::shared_ptr;

int main() {
  ConcreteFactory fc;
  shared_ptr<Product> p = fc.factoryMethod();
  p->use();

  return 0;
}
