#ifndef AND_QUERY_H_
#define AND_QUERY_H_

#include "binary_query.h"

class AndQuery : public BinaryQuery {
  friend Query operator&(const Query&, const Query&);

 private:
  AndQuery(const Query& left, const Query& right)
      : BinaryQuery(left, right, "&") {
#ifndef NDEBUG
    std::cout << "AndQuery(const Query& q)" << std::endl;
#endif /* ifndef  */
  }
  QueryResult eval(const TextQuery&) const override;
};

Query operator&(const Query&, const Query&);

inline Query operator&(const Query& lhs, const Query& rhs) {
  return std::shared_ptr<QueryBase>(new AndQuery(lhs, rhs));
}

#endif /* ifndef AND_QUERY_H_ */
