#include <atomic>
#include <iostream>
#include <thread>

using namespace std;

int sharedValue = 0;
atomic<int> flag(0);

void f1() {
  int count = 0;
  while (count < 10000000) {
    // 全为seq_cst也不行，两个线程可能同时读到temp_flag为0,
    // 然后store 1
    int temp_flag = flag.load(memory_order_seq_cst);
    if (temp_flag == 0) {
      flag.store(1, memory_order_seq_cst);
      ++sharedValue;
      flag.store(0, memory_order_seq_cst);
      ++count;
    }
  }
}

void f2() {
  int count = 0;
  while (count < 10000000) {
    int expected = 0;
    if (flag.compare_exchange_strong(expected, 1, memory_order_relaxed)) {
      // if (flag.compare_exchange_strong(expected, 1, memory_order_acquire)) {
      ++sharedValue;
      flag.store(0, memory_order_relaxed);
      // flag.store(0, memory_order_release);
      ++count;
    }
  }
}

int main(int argc, char *argv[]) {
  for (int i = 0; i < 10000; ++i) {
    thread t1(f2);

    f2();
    t1.join();

    cout << sharedValue << endl;
    sharedValue = 0;
  }
  return 0;
}
