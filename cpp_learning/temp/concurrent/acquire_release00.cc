#include <atomic>
#include <iostream>
#include <thread>

using namespace std;

int i = 0;

atomic<int> a(0);
atomic<int> b(0);
atomic<int> r1(0);
atomic<int> r2(0);

void f1() {
  a.store(1, memory_order_relaxed);
  r1.store(b, memory_order_relaxed);
}

void f2() {
  b.store(1, memory_order_relaxed);
  r2.store(a, memory_order_relaxed);
}

int main(int argc, char *argv[]) {
  while (true) {
    thread t1(f1);
    thread t2(f2);

    t1.join();
    t2.join();

    if (r1 == 0 && r2 == 0) {
      cout << "iteration " << i << ": " << r1 << " " << r2 << endl;
    }
    a.store(0);
    b.store(0);
    r1.store(0);
    r2.store(0);
    ++i;
  }
  return 0;
}
