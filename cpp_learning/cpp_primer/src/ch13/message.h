#ifndef MESSAGE_H_
#define MESSAGE_H_ value

#include <iostream>
#include <set>
#include <string>

#include "folder.h"

class Message {
  friend class Folder;
  friend void swap(Message &lhs, Message &rhs);
  friend void listContainingFolders(const Message &m);

 public:
  explicit Message(const std::string &str = "") : contents(str) {}
  Message(const Message &m) : contents(m.contents), folders(m.folders) {
    add_to_Folders(m);
  }
  Message(Message &&m) : contents(std::move(m.contents)) { move_Folders(&m); }
  Message &operator=(const Message &rhs) {
    remove_from_Folders();
    contents = rhs.contents;
    folders = rhs.folders;
    add_to_Folders(rhs);
    return *this;
  }
  Message &operator=(Message &&rhs) {
    if (this != &rhs) {
      remove_from_Folders();
      contents = std::move(rhs.contents);
      move_Folders(&rhs);
    }
    return *this;
  }
  ~Message() { remove_from_Folders(); }
  void save(Folder &f) {
    folders.insert(&f);
    f.addMsg(this);
  }
  void remove(Folder &f) {
    folders.erase(&f);
    f.remMsg(this);
  }
  void addFolder(Folder *const pf) { folders.insert(pf); }
  void removeFolder(Folder *const pf) { folders.erase(pf); }
  std::string getStr() const { return contents; }

 private:
  std::string contents;
  std::set<Folder *> folders;
  void add_to_Folders(const Message &m) {
    for (auto &f : m.folders) {
      f->addMsg(this);
    }
  }
  void remove_from_Folders() {
    for (auto &f : folders) {
      f->remMsg(this);
    }
  }
  void move_Folders(Message *m) {
    folders = std::move(m->folders);
    for (auto f : folders) {
      f->remMsg(m);
      // 可能会抛出异常
      f->addMsg(this);
    }
    m->folders.clear();
  }
};

void swap(Message &lhs, Message &rhs) {
  using std::swap;
  for (auto &f : lhs.folders) {
    f->remMsg(&lhs);
  }

  for (auto &f : rhs.folders) {
    f->remMsg(&rhs);
  }

  swap(lhs.contents, rhs.contents);
  swap(lhs.folders, rhs.folders);

  for (auto &f : lhs.folders) {
    f->addMsg(&lhs);
  }

  for (auto &f : rhs.folders) {
    f->addMsg(&rhs);
  }
}

void listContainingFolders(const Message &m) {
  std::cout << "---" << std::endl;
  for (const auto &f : m.folders) {
    std::cout << f << std::endl;
  }
}

Folder::Folder(const Folder &f) {
  for (auto &m : f.messages) {
    m->addFolder(this);
  }
}

Folder &Folder::operator=(const Folder &rhs) {
  for (auto &m : messages) {
    m->remove(*this);
  }

  for (auto &m : rhs.messages) {
    m->save(*this);
  }

  return *this;
}

Folder::~Folder() {
  for (auto &m : messages) {
    m->remove(*this);
  }
}

void swap(Folder &lhs, Folder &rhs) {
  using std::swap;

  for (auto &m : lhs.messages) {
    m->removeFolder(&lhs);
  }

  for (auto &m : rhs.messages) {
    m->removeFolder(&rhs);
  }

  swap(lhs.messages, rhs.messages);

  for (auto &m : lhs.messages) {
    m->addFolder(&lhs);
  }

  for (auto &m : rhs.messages) {
    m->addFolder(&rhs);
  }
}

void listFolder(const Folder &f) {
  std::cout << "---" << std::endl;
  for (auto &m : f.messages) {
    std::cout << m->getStr() << std::endl;
  }
}

#endif /* ifndef MESSAGE_H_ */
