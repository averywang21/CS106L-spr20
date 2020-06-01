
#ifndef OSTREAMLOCK_H
#define OSTREAMLOCK_H
/**
 * Presents the implementation of two stream manipulators
 * designed to make insertion into ostreams thread-safe.
 */

#include <ostream>
#include <iostream>
#include <mutex>
#include <memory>
#include <map>



static std::mutex mapLock;
static std::map<std::ostream *, std::unique_ptr<std::mutex>> streamLocks;

std::ostream& oslock(std::ostream& os) {
  std::ostream *ostreamToLock = &os;
  if (ostreamToLock == &std::cerr) ostreamToLock = &std::cout;
  mapLock.lock();
  std::unique_ptr<std::mutex>& up = streamLocks[ostreamToLock];
  if (up == nullptr) {
    up.reset(new std::mutex);
  }
  mapLock.unlock();
  up->lock();
  return os;
}

std::ostream& osunlock(std::ostream& os) {
  std::ostream *ostreamToLock = &os;
  if (ostreamToLock == &std::cerr) ostreamToLock = &std::cout;
  mapLock.lock();
  auto found = streamLocks.find(ostreamToLock);
  mapLock.unlock();
  if (found == streamLocks.end())
    throw "unlock inserted into stream that has never been locked.";
  std::unique_ptr<std::mutex>& up = found->second;
  up->unlock();
  return os;
}

#endif // OSTREAMLOCK_H
