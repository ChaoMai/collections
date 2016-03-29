#ifndef IN_MEM_LOG_H_
#define IN_MEM_LOG_H_

#include <string>
#include <thread>

struct Event {
  std::thread::id id;
  std::string msg;
  std::size_t param;
};

static constexpr int BUFFER_SIZE = 65536;
extern Event g_events[BUFFER_SIZE];
std::size_t g_pos;

inline void log(const std::string& msg, std::size_t param) {}

#endif /* ifndef IN_MEM_LOG_H_ */
