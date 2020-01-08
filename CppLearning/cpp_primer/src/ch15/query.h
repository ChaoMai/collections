#ifndef QUERY_H_
#define QUERY_H_

#define NDEBUG

#include <iostream>
#include <memory>
#include <string>

#include "query_base.h"
#include "query_result.h"
#include "text_query.h"
#include "word_query.h"

class Query {
  friend Query operator~(const Query&);
  friend Query operator&(const Query&, const Query&);
  friend Query operator|(const Query&, const Query&);

 public:
  Query(const std::string&);
  QueryResult eval(const TextQuery& t) const { return q_->eval(t); }
  std::string rep() const {
#ifndef NDEBUG
    std::cout << "Query::rep()" << std::endl;
#endif /* ifndef  */
    return q_->rep();
  }

 private:
  Query(std::shared_ptr<QueryBase> query) : q_(query) {
#ifndef NDEBUG
    std::cout << "Query(std::shared_ptr<QueryBase> query) " << std::endl;
#endif /* ifndef  */
  }

  std::shared_ptr<QueryBase> q_;
};

std::ostream& operator<<(std::ostream&, const Query&);

inline Query::Query(const std::string& s) : q_(new WordQuery(s)) {
#ifndef NDEBUG
  std::cout << "Query::Query(const std::string& s) " << s << std::endl;
#endif /* ifndef  */
}

#endif /* ifndef QUERY_H_ */
