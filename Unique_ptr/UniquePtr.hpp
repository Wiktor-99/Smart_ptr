#pragma once
#include <utility>
#include<iostream>
namespace nostd {

template <typename T>
class unique_ptr {
  public:
    unique_ptr();
    explicit unique_ptr(T *ptr);
    unique_ptr(const unique_ptr &other) = delete;
    unique_ptr(unique_ptr &&other);
    ~unique_ptr();

    unique_ptr &operator=(const unique_ptr &ptr) = delete;
    unique_ptr &operator=(unique_ptr &&ptr);

    T &operator*() const;
    T *operator->() const;

    T *get() const;
    T *release();
    void reset(T *newPtr = nullptr);

  private:
    T *ptr_{};
};
template <typename T>
unique_ptr<T>::unique_ptr() : ptr_{nullptr} {}

template <typename T>
unique_ptr<T>::unique_ptr(T *ptr) : ptr_{ptr} {}

template <typename T>
unique_ptr<T>::unique_ptr(unique_ptr<T> &&other) : ptr_{other.release()} {}

template <typename T>
unique_ptr<T>::~unique_ptr() {
    delete ptr_;
}

template <typename T>
unique_ptr<T> &unique_ptr<T>::operator=(unique_ptr<T> &&other) {
    if (this != &other) {
        delete ptr_;
        ptr_ = other.release();
    }
    return *this;
}

template <typename T>
T &unique_ptr<T>::operator*() const {
    return *ptr_;
}

template <typename T>
T *unique_ptr<T>::operator->() const {
    return ptr_;
}

template <typename T>
T *unique_ptr<T>::get() const {
    return ptr_;
}

template <typename T>
void unique_ptr<T>::reset(T *newPtr) {
    delete ptr_;
    ptr_ = newPtr;
}
template <typename T>
T *unique_ptr<T>::release() {
    T *tmp{};
    std::swap(tmp, ptr_);
    return tmp;
}

} // namespace nostd
