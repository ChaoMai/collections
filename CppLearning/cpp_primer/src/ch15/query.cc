#include "query.h"

#include <iostream>
#include <string>

#include "word_query.h"

using std::ostream;
using std::string;

ostream& operator<<(ostream& os, const Query& query) {
  return os << query.rep();
}
