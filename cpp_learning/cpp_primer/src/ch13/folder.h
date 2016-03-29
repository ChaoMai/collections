#ifndef FOLDER_H_
#define FOLDER_H_

#include <iostream>
#include <set>
#include <string>

class Message;

class Folder {
  friend void swap(Folder &lhs, Folder &rhs);
  friend void listFolder(const Folder &f);

 public:
  Folder() = default;
  Folder(const Folder &f);
  Folder &operator=(const Folder &rhs);
  ~Folder();
  // 可能会抛出异常
  void addMsg(Message *const pm) { messages.insert(pm); }
  void remMsg(Message *const pm) { messages.erase(pm); }

 private:
  std::set<Message *> messages;
};

#endif /* ifndef FOLDER_H_ */
