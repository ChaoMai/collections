#include <atomic>
#include <iostream>
#include <thread>

using namespace std;

atomic<int> a(0);
atomic<int> b(0);

void f1() { a.store(1, memory_order_release); }

void f2() {
  while (a.load(memory_order_acquire) != 0) {
    b.store(a.load(), memory_order_relaxed);
  }
}

int main(int argc, char *argv[]) {
  thread t1;
  thread t2;
  while (true) {
    t1 = thread(f1);
    t2 = thread(f2);
    t1.join();
    t2.join();

    if (b.load() == 0) {
      cout << b.load() << endl;
    }

    a.store(0);
    b.store(0);
  }
  return 0;
}
