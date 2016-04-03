#include "text_query.h"

#include <iostream>
#include <memory>
#include <vector>
#include <set>
#include <sstream>
#include <string>

#include "query_result.h"

using std::getline;
using std::ifstream;
using std::vector;
using std::shared_ptr;
using std::set;
using std::string;
using std::istringstream;

TextQuery::TextQuery(ifstream& is) : file_(new vector<string>) {
  string text;
  while (getline(is, text)) {
    file_->push_back(text);
    auto n = file_->size() - 1;
    istringstream line(text);
    string word;
    while (line >> word) {
      auto& lines = wm_[word];
      if (!lines) {
        lines.reset(new set<line_no>);
      }
      lines->insert(n);
    }
  }
}

QueryResult TextQuery::query(const string& sought) const {
  static shared_ptr<set<line_no>> nodata(new set<line_no>);
  auto loc = wm_.find(sought);
  if (loc == wm_.end()) {
    return QueryResult(sought, nodata, file_);
  } else {
    return QueryResult(sought, loc->second, file_);
  }
}
