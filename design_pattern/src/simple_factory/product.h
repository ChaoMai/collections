#ifndef PRODUCT_H_
#define PRODUCT_H_

class Product {
 public:
  Product() = default;
  virtual ~Product() = default;

  virtual void use() = 0;
};

#endif /* ifndef PRODUCT_H_ */
