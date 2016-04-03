#ifndef WORD_QUERY_H_
#define WORD_QUERY_H_

#include <string>

#ifndef NDEBUG
#include <iostream>
#endif

#include "query_base.h"
#include "query_result.h"
#include "text_query.h"

class Query;

class WordQuery : public QueryBase {
  friend class Query;

 private:
  WordQuery(const std::string& s) : query_word_(s) {
#ifndef NDEBUG
    std::cout << "WordQuery(const Query& s) " << s << std::endl;
#endif /* ifndef  */
  }
  QueryResult eval(const TextQuery& t) const { return t.query(query_word_); }
  std::string rep() const {
#ifndef NDEBUG
    std::cout << "WordQuery::rep() " << query_word_ << std::endl;
#endif /* ifndef  */
    return query_word_;
  }

  std::string query_word_;
};

#endif /* ifndef WORD_QUERY_H_ */
