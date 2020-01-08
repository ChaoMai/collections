#include "not_query.h"

#include <memory>
#include <set>

#include "query_result.h"
#include "text_query.h"

using std::make_shared;
using std::set;

QueryResult NotQuery::eval(const TextQuery& text) const {
  auto result = query_.eval(text);
  auto ret_lines = make_shared<set<line_no>>();
  auto beg = result.begin();
  auto end = result.end();

  auto sz = result.get_file()->size();

  for (size_t n = 0; n != sz; ++n) {
    if (beg == end || *beg != n) {
      ret_lines->insert(n);
    } else if (beg != end) {
      ++beg;
    }
  }

  return QueryResult(rep(), ret_lines, result.get_file());
}
