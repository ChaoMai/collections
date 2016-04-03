#ifndef BINARY_QUERY_H_
#define BINARY_QUERY_H_

#include <string>

#ifndef NDEBUG
#include <iostream>
#endif

#include "query.h"
#include "query_base.h"

class BinaryQuery : public QueryBase {
 protected:
  BinaryQuery(const Query& l, const Query& r, std::string s)
      : lhs_(l), rhs_(r), opSym_(s) {
#ifndef NDEBUG
    std::cout << "BinaryQuery(const Query& q)" << std::endl;
#endif /* ifndef  */
  }
  std::string rep() const override {
#ifndef NDEBUG
    std::cout << "BinaryQuery::rep() " << opSym_ << std::endl;
#endif
    return "(" + lhs_.rep() + " " + opSym_ + " " + rhs_.rep() + ")";
  }

  Query lhs_;
  Query rhs_;
  std::string opSym_;
};

#endif /* ifndef BINARY_QUERY_H_ */
