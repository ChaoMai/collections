#ifndef QUERY_BASE_H_
#define QUERY_BASE_H_

#include <string>

#include "query_result.h"
#include "text_query.h"

class QueryBase {
  friend class Query;

 protected:
  using line_no = TextQuery::line_no;
  virtual ~QueryBase() = default;

 private:
  virtual QueryResult eval(const TextQuery&) const = 0;
  virtual std::string rep() const = 0;
};

#endif /* ifndef QUERY_BASE_H_ */
