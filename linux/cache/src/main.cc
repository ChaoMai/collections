#include <array>
#include <chrono>
#include <iostream>
#include <tuple>

using namespace std;

class Timer {
 public:
  Timer() { starting_time = std::chrono::high_resolution_clock::now(); }

  ~Timer() {
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(
                     std::chrono::high_resolution_clock::now() - starting_time)
                     .count()
              << std::endl;
  }

 private:
  std::chrono::high_resolution_clock::time_point starting_time;
};

constexpr size_t size = 256 * 1024 * 1024;

void test1() {
  int *arr = new int[size];
  {
    Timer t;
    for (size_t i = 0; i < size; ++i) {
      arr[i] *= 3;
    }
  }

  {
    Timer t;
    for (size_t i = 0; i < size; i += 16) {
      arr[i] *= 3;
    }
  }
}

void test2() {
  int *arr = new int[size];

  for (size_t k = 1; k < 1024; ++k) {
    Timer t;
    for (size_t i = 0; i < size; i += k) {
      arr[i] *= 3;
    }
    cout << k << ", ";
  }
}

void test3() {
  int *arr = new int[size];

  for (size_t k = 1; k < 1024; ++k) {
    Timer t;
    for (size_t i = 0; i * k < size; ++i) {
      arr[i * k] += 1;
    }
    cout << k << ", ";
  }
}

void test4() {
  int *arr = new int[2];

  {
    Timer t;
    for (size_t i = 0; i < size; ++i) {
      ++arr[0];
      ++arr[0];
    }
  }

  {
    Timer t;
    for (size_t i = 0; i < size; ++i) {
      ++arr[0];
      ++arr[1];
    }
  }
}

int main(int argc, char *argv[]) {
  // test1();
  // test2();
  // test3();
  test4();
  return 0;
}
