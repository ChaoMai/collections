#include "query_result.h"

#include <iostream>
#include <vector>
#include <string>

using std::endl;
using std::ostream;
using std::string;
using std::vector;

ostream& operator<<(std::ostream& os, const QueryResult& qr) {
  os << qr.sought_ << " occurs " << qr.lines_->size() << " "
     << (qr.lines_->size() <= 1 ? "time" : "times") << endl;

  for (auto num : *qr.lines_) {
    os << "\t(line " << num + 1 << ") "
       << *(qr.file_->begin() +
            static_cast<vector<string>::difference_type>(num))
       << endl;
  }
  return os;
}
