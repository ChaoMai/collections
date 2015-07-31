//
// Created by chaomai on 6/8/15.
//

#ifndef CPPLEARNING_UTILS_H
#define CPPLEARNING_UTILS_H

class timer {
 public:
  timer() {
    starting_time = std::chrono::high_resolution_clock::now();
  }

  ~timer() {
    std::cout << "duration: " <<
    std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - starting_time).count()
    << std::endl;
  }

 private:
  std::chrono::high_resolution_clock::time_point starting_time;
};

#endif //CPPLEARNING_UTILS_H
