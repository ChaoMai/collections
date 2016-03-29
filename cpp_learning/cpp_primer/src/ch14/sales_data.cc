#include "sales_data.h"

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::istream;
using std::ostream;

istream& operator>>(istream& is, Sales_data& item) {
  double price = 0.0;
  is >> item.bookNo >> item.units_sold >> price;
  if (is) {
    item.revenue = price * item.units_sold;
  } else {
    item = Sales_data();
  }
  return is;
}

ostream& operator<<(ostream& os, const Sales_data& sd) {
  os << sd.bookNo << " " << sd.units_sold << " " << sd.revenue;
  return os;
}

Sales_data operator+(const Sales_data& lhs, const Sales_data& rhs) {
  // Sales_data sum = lhs;
  // sum.units_sold += rhs.units_sold;
  // sum.revenue += rhs.revenue;
  // return sum;

  Sales_data sum = lhs;
  sum += rhs;
  return sum;
}

// Sales_data& Sales_data::operator+=(const Sales_data& rhs) {
// units_sold += rhs.units_sold;
// revenue += rhs.revenue;
// return *this;
// }

Sales_data& Sales_data::operator+=(const Sales_data& rhs) {
  Sales_data tmp = *this;
  *this = tmp + rhs;
  return *this;
}

Sales_data& Sales_data::operator=(const std::string& s) {
  // 不是初始化，其他成员的值无法清除
  // bookNo = s;
  *this = Sales_data(s);
  return *this;
}

bool operator==(const Sales_data& lhs, const Sales_data& rhs) {
  return lhs.isbn() == rhs.isbn() && lhs.units_sold == rhs.units_sold &&
         lhs.revenue == rhs.revenue;
}

bool operator!=(const Sales_data& lhs, const Sales_data& rhs) {}
