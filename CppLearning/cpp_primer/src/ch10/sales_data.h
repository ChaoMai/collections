#ifndef SALES_DATA_H_
#define SALES_DATA_H_

#include <iostream>

class Sales_data {
 public:
  Sales_data() = default;
  Sales_data(const std::string &s) : bookNo(s) {}
  Sales_data(const std::string &s, unsigned n, double p)
      : bookNo(s), units_sold(n), revenue(n * p) {}

  std::string isbn() const { return bookNo; }
  Sales_data &combine(const Sales_data &);

 private:
  inline double avg_price() const;

 private:
  std::string bookNo;
  unsigned units_sold = 0;
  double revenue = 0.0;
};

inline double Sales_data::avg_price() const {
  return units_sold ? revenue / units_sold : 0;
}

#endif /* ifndef SALES_DATA_H_ */
