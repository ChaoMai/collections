#ifndef OR_QUERY_H_
#define OR_QUERY_H_

#ifndef NDEBUG
#include <iostream>
#endif

#include "binary_query.h"

class OrQuery : public BinaryQuery {
  friend Query operator|(const Query&, const Query&);

 private:
  OrQuery(const Query& left, const Query& right)
      : BinaryQuery(left, right, "|") {
#ifndef NDEBUG
    std::cout << "OrQuery(const Query& left, const Query& right)" << std::endl;
#endif /* ifndef  */
  }
  QueryResult eval(const TextQuery&) const override;
};

Query operator|(const Query&, const Query&);

inline Query operator|(const Query& lhs, const Query& rhs) {
  return std::shared_ptr<QueryBase>(new OrQuery(lhs, rhs));
}

#endif /* ifndef OR_QUERY_H_ */
