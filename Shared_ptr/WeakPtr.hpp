#pragma once

#include "CounterBlock.hpp"
#include "SharedPtr.hpp"

namespace nostd {
template <typename T>
class weak_ptr {
  public:
    weak_ptr() noexcept = default;
    weak_ptr(const weak_ptr<T> &other) noexcept;
    weak_ptr(const shared_ptr<T> &sharedPtr) noexcept;

    weak_ptr(weak_ptr<T> &&other) noexcept;

    weak_ptr<T> &operator=(const weak_ptr<T> &other) noexcept;
    weak_ptr<T> &operator=(const shared_ptr<T> &sharedPtr) noexcept;
    weak_ptr<T> &operator=(weak_ptr<T>&& other) noexcept;

    std::size_t use_count() const{return counterBlock_->getWeakRefCounter();};
    bool expired() const noexcept { return use_count() == 0; }
    void reset() noexcept;
    nostd::shared_ptr<T> lock() const noexcept;

  private:
    void deleteResource();

  private:
    T *ptr_{};
    CounterBlock<T> *counterBlock_{};
};
template<typename T>
weak_ptr<T>::weak_ptr(const weak_ptr<T> &other)noexcept: ptr_{other.ptr_}, counterBlock_{other.counterBlock_}
{}
} // namespace nostd