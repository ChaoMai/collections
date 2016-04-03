#include "and_query.h"

#include <algorithm>
#include <iterator>
#include <memory>
#include <set>

#include "query_result.h"
#include "text_query.h"

using std::inserter;
using std::make_shared;
using std::set;
using std::set_intersection;

QueryResult AndQuery::eval(const TextQuery& text) const {
  auto right = rhs_.eval(text);
  auto left = lhs_.eval(text);

  auto ret_lines = make_shared<set<line_no>>();
  set_intersection(left.begin(), left.end(), right.begin(), right.end(),
                   inserter(*ret_lines, ret_lines->begin()));

  return QueryResult(rep(), ret_lines, left.get_file());
}
