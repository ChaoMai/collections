#include "or_query.h"

#include <memory>
#include <set>

#include "query_result.h"
#include "text_query.h"

using std::make_shared;
using std::set;

QueryResult OrQuery::eval(const TextQuery& text) const {
  auto right = rhs_.eval(text);
  auto left = lhs_.eval(text);

  auto ret_lines = make_shared<set<line_no>>(left.begin(), left.end());
  ret_lines->insert(right.begin(), right.end());

  return QueryResult(rep(), ret_lines, left.get_file());
}
