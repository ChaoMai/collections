#include <memory>

#include "factory.h"
#include "product.h"

using std::shared_ptr;

int main() {
  shared_ptr<Product> p = Factory::createProduct();
  p->use();

  shared_ptr<Product> p1 = Factory::createProduct("1");
  p1->use();
  return 0;
}
