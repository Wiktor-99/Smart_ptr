#pragma once

#include "CounterBlock.hpp"

namespace nostd {

template <typename T>
class shared_ptr {
    shared_ptr(
        T *ptr = nullptr, std::function<void(T *)> deleter = [](T *ptr) { delete ptr; });
    shared_ptr(const shared_ptr<T> &other) noexcept;
    shared_ptr(shared_ptr<T> &&other) noexcept;
    ~shared_ptr();

    shared_ptr<T> &operator=(const shared_ptr<T> &other) noexcept;
    shared_ptr<T> &operator=(shared_ptr<T> &&other) noexcept;

    T &operator*() const noexcept{return *ptr_;}
    T *operator->() const noexcept{return ptr_;}
    std::size_t use_count() const noexcept { return static_cast<std::size_t>(counterBlock_->getSharedrefCounter()); }
    T *get() const noexcept{return ptr_;}
    void reset(
        T *ptr = nullptr, std::function<void(T *)> deleter = [](T *ptr) { delete ptr; }) noexcept;
    explicit operator bool() const noexcept { return ptr_ != nullptr; }

  private:
    void deleteResource();

  private:
    T *ptr_{};
    CounterBlock<T> *counterBlock_{};
};
template <typename T>
void shared_ptr<T>::deleteResource() {
    if (counterBlock_) {
        counterBlock_->decrementRefCounter();
        if (counterBlock_->getSharedrefCounter() == 0) {
            counterBlock_->deleter_(ptr_);
            delete counterBlock_;
        }
    }
}

template <typename T>
shared_ptr<T>::shared_ptr(T *ptr, std::function<void(T *)> deleter)
    : ptr_{ptr}, counterBlock_{new CounterBlock<T>(deleter)} {}
template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr<T> &other) noexcept {
    ptr_ = other.ptr_;
    counterBlock_ = other.counterBlock_;
    counterBlock_->incrementRefCounter();
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
        deleteResource();
        ptr_ = other.ptr_;
        counterBlock_ = other.counterBlock_;
        counterBlock_->incrementRefCounter();
    }
    return *this;
}
template <typename T>
shared_ptr<T> &shared_ptr<T>::operator=(shared_ptr<T> &&other) noexcept {
    if (&other != this) {
        deleteResource();
        ptr_ = other.ptr_;
        counterBlock_ = other.counterBlock_;
        other.ptr_ = nullptr;
        other.counterBlock_ = nullptr;
    }
    return *this;
}
template <typename T>
shared_ptr<T>::~shared_ptr() {
    deleteResource();
}
template <typename T>
void shared_ptr<T>::reset(T *ptr, std::function<void(T *)> deleter) noexcept {
    deleteResource();
    ptr_ = ptr;
    counterBlock_ = new CounterBlock<T>(deleter);
}

} // namespace nostd