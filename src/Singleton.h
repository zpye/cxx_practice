#ifndef CXX_PRACTICE_SINGLETON_H
#define CXX_PRACTICE_SINGLETON_H

#include <mutex>
#include <utility>

// use call_once
template <typename T>
class Singleton {
 public:
  template <typename... Args>
  static T* GetInstance(Args&&... args) {
    std::call_once(Singleton<T>::oc, [&] {
      static T inst(std::forward<Args>(args)...);
      p_inst = &inst;
    });
    return p_inst;
  }

  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;

 protected:
  Singleton() = default;
  ~Singleton() = default;

 private:
  static T* p_inst;
  static std::once_flag oc;
};

template <typename T>
T* Singleton<T>::p_inst = nullptr;

template <typename T>
std::once_flag Singleton<T>::oc;

// use local static
template <typename T>
class SingletonNoArg {
 public:
  static T* GetInstance() {
    static T inst;
    return &inst;
  }

  SingletonNoArg(const SingletonNoArg&) = delete;
  SingletonNoArg& operator=(const SingletonNoArg&) = delete;

 protected:
  SingletonNoArg() = default;
  ~SingletonNoArg() = default;
};

#endif  // CXX_PRACTICE_SINGLETON_H