#ifndef QUERY_RESULT_H_
#define QUERY_RESULT_H_

#include <iostream>
#include <memory>
#include <set>
#include <vector>

class QueryResult {
  friend std::ostream& operator<<(std::ostream&, const QueryResult&);

 public:
  using line_no = std::vector<std::string>::size_type;
  QueryResult(std::string s, std::shared_ptr<std::set<line_no>> p,
              std::shared_ptr<std::vector<std::string>> f)
      : sought_(s), lines_(p), file_(f) {}
  std::set<line_no>::iterator begin() { return lines_->begin(); }
  std::set<line_no>::iterator end() { return lines_->end(); }
  std::shared_ptr<std::vector<std::string>> get_file() { return file_; }

 private:
  std::string sought_;
  std::shared_ptr<std::set<line_no>> lines_;
  std::shared_ptr<std::vector<std::string>> file_;
};

#endif /* ifndef QUERY_RESULT_H_ */
