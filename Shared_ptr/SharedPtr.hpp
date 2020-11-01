#pragma once

#include <functional>

#include "CounterBlock.hpp"

namespace nostd {

template <typename T>
class shared_ptr {
    using Deleter = std::function<void(T *)>;

    shared_ptr(
        T *ptr = nullptr, Deleter deleter = [](T *ptr) { delete ptr; });
    shared_ptr(const shared_ptr<T> &other) noexcept;
    shared_ptr(shared_ptr<T> &&other) noexcept;

    shared_ptr<T> &operator=(const shared_ptr<T> &other) noexcept;
    shared_ptr<T> &operator=(shared_ptr<T> &&other) noexcept;

  private:
    void deleteRescource();

  private:
    T *ptr_{};
    Deleter deleter_ = [](T *ptr) { delete ptr; };
    CounterBlock *counterBlock_{};
};

template <typename T>
shared_ptr<T>::shared_ptr(T *ptr, Deleter deleter)
    : ptr_{ptr}, deleter_{deleter}, counterBlock_{new CounterBlock] {
    if (ptr_) {
        counterBlock_->incrementRefCounter();
    }
}
template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr<T> &other) noexcept {
    ptr_ = other.ptr_;
    counterBlock_ = other.counterBlock_;
        if (ptr_) {
            counterBlock_->incrementRefCounter();
        }
}
template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr<T> &&other) noexcept {
    ptr_ = other.ptr_;
    counterBlock_ = other.counterBlock_;
    other.ptr_ = nullptr;
    other.counterBlock_ = nullptr;
}
template <typename T>
shared_ptr<T> &shared_ptr<T>::operator=(const shared_ptr<T> &other) noexcept {
    if (&other != this) {
        deleteRescource();
        ptr_ = other.ptr_;
        counterBlock_ = other.counterBlock_;
        if (ptr_) {
            counterBlock_->incrementRefCounter();
        }
    }
    return *this;
}
template <typename T>
shared_ptr<T> &shared_ptr<T>::operator=(shared_ptr<T> &&other) noexcept {
    if (&other != this) {
        deleteRescource();
        ptr_ = other.ptr_;
        counterBlock_ = other.counterBlock_;
        other.ptr_ = nullptr;
        other.counterBlock_ = nullptr;
    }
    return *this;
}

} // namespace nostd