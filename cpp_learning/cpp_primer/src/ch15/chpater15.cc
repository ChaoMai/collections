#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "bulk_quote.h"
#include "bulk_quote1.h"
#include "bulk_quote2.h"
#include "quote.h"

#include "circle.h"
#include "line.h"
#include "point.h"
#include "rectangle.h"

#include "and_query.h"
#include "not_query.h"
#include "or_query.h"
#include "query.h"
#include "text_query.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::make_shared;
using std::ostream;
using std::shared_ptr;
using std::string;
using std::vector;

double print_total(ostream &os, const Quote &item, size_t n) {
  double ret = item.net_price(n);
  os << "ISBN: " << item.isbn() << "# sold: " << n << " total due: " << ret
     << endl;
  return ret;
}

void t1() {
  class C {
   public:
    C() = default;
    C(const C &) = delete;
    C &operator=(const C &) = delete;
    C(C &&) = delete;
    C &operator=(C &&) = delete;
  };

  C c;
  // C c1 = std::move(C());
}

void t2() {
  Quote item;
  BulkQuote bulk;
  Quote *p = &item;
  p = &bulk;
  Quote &r = bulk;
}

void t3() {
  Quote item("awef", 12);
  BulkQuote bulk("awqef", 12, 23, 0.5);

  print_total(cout, item, 10);
  print_total(cout, bulk, 40);

  Quote *pq = &bulk;
  BulkQuote *pb = dynamic_cast<BulkQuote *>(pq);
  print_total(cout, *pb, 40);
  BulkQuote *pb1 = static_cast<BulkQuote *>(pq);
  print_total(cout, *pb, 40);
}

void t4() {
  class D : public Quote {
   public:
    // int net_price(size_t n) const { return n * price; }
    double net_price(double n) const { return n * price; }
  };
}

void t5() {
  Quote item("awef", 12);
  BulkQuote bulk("ijojponawqef", 120000, 23, 0.5);

  item.debug();
  cout << "---" << endl;
  bulk.debug();

  // DiscQuote d;
}

void draw_shape(Shape &s) { s.draw(); }

void t6() {
  Point p(1, 2);
  cout << p << endl;

  Line l({1, 2}, {3, 5});
  l.draw();
  l.move(1, 1);
  l.draw();

  Line l2 = l;
  l2.draw();
  draw_shape(l2);
}

void t7() {
  Rectangle r;
  r.draw();
  Rectangle r1({12, 32}, 234, 4234);
  r1.draw();
  r = r1;
  r.draw();
  r.move(12, 3242);
  draw_shape(r);
}

void t8() {
  Circle c;
  c.draw();
  Circle c1({132, 23}, 12124);
  c1.draw();
  c = c1;
  draw_shape(c);
}

void t9() {
  class B {
   public:
    virtual int fcn() {
      cout << "base" << endl;
      return 1;
    }
  };

  class D : public B {
   public:
    using B::fcn;
    int fcn(int i) {
      cout << "derive " << i << endl;
      return 1;
    }
  };

  D d;
  d.fcn();
  d.fcn(1);
}

void t10() {
  class B {
   public:
    B() = default;
    B(const B &) = delete;
    B &operator=(const B &) {
      cout << "c" << endl;
      return *this;
    }
    virtual ~B() = default;
  };

  class D : public B {};

  B b;
  b = b;
  b = std::move(b);
  // B b1(b);
  // B b2(std::move(b));
}

void t11() {
  BulkQuote1 b;
  cout << "---" << endl;
  BulkQuote1 b1(b);
  cout << "---" << endl;
  b1 = b;
  cout << "---" << endl;
}

void t12() {
  BulkQuote2 b;
  cout << "---" << endl;
  BulkQuote2 b1("book", 20, 50, 0.1);
  cout << "---" << endl;
}

void t13() {
  class C {
   public:
    C(const C &) = default;
  };

  // C c;
}

void t14() {
  vector<Quote> vq;
  vq.emplace_back("joininnaw", 15);
  vq.push_back(BulkQuote("awfawnn", 15, 10, 0.4));

  for (const auto &q : vq) {
    cout << q.net_price(20) << endl;
  }
}

void t15() {
  vector<shared_ptr<Quote>> vq;
  vq.push_back(make_shared<Quote>("joininnaw", 15));
  vq.push_back(make_shared<BulkQuote>("awfawnn", 15, 10, 0.4));

  for (const auto &q : vq) {
    cout << q->net_price(20) << endl;
  }
}

void t16() {
  BulkQuote1 bq;
  cout << "---" << endl;
  BulkQuote1 bq1(std::move(bq));
  cout << "---" << endl;

  Quote q;
  cout << "---" << endl;
  Quote q1(std::move(q));
  cout << "---" << endl;
}

void t17() {
  auto ifs = ifstream("../src/data/story.txt", ifstream::in);
  TextQuery tq(ifs);
  cout << tq.query("is") << endl;
  cout << tq.query("no") << endl;
  cout << tq.query("she") << endl;

  Query q = Query("is") & Query("no") | Query("she");
  cout << q.eval(tq) << endl;

  Query q1 = ~Query("no") | Query("she");
  cout << q1.eval(tq) << endl;
}

void t18() {
  struct Erdos {
    Erdos() { whoAmIReally(); }
    virtual void whoAmIReally() { cout << "I really am Erdos\n"; }
  };

  struct Fermat : public Erdos {
    virtual void whoAmIReally() { cout << "I really am Fermat\n"; }
  };

  Erdos s;
  Fermat f;
}

int main(int argc, char *argv[]) {
  // t1();
  // t2();
  // t3();
  // t4();
  // t5();
  // t6();
  // t7();
  // t8();
  // t9();
  // t10();
  // t11();
  // t12();
  // t13();
  // t14();
  // t15();
  // t16();
  // t17();
  t18();
  return 0;
}
