#ifndef NOT_QUERY_H_
#define NOT_QUERY_H_

#include <string>

#ifndef NDEBUG
#include <iostream>
#endif

#include "query.h"
#include "query_base.h"

class NotQuery : public QueryBase {
  friend Query operator~(const Query&);

 private:
  NotQuery(const Query& q) : query_(q) {
#ifndef NDEBUG
    std::cout << "NotQuery(const Query& q)" << std::endl;
#endif /* ifndef  */
  }
  QueryResult eval(const TextQuery&) const override;
  std::string rep() const override {
#ifndef NDEBUG
    std::cout << "NotQuery::rep()" << std::endl;
#endif /* ifndef  */
    return "~(" + query_.rep() + ")";
  }

  Query query_;
};

Query operator~(const Query&);

inline Query operator~(const Query& operand) {
  return std::shared_ptr<QueryBase>(new NotQuery(operand));
}

#endif /* ifndef NOT_QUERY_H_ */
