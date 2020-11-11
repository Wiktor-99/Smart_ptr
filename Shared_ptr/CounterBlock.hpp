#pragma once

#include <atomic>
#include <functional>

namespace nostd {
template <typename T>
class CounterBlock {

  public:
    using Deleter = std::function<void(T *)>;

  public:
    CounterBlock(Deleter deleter = [](T *ptr) { delete ptr; }) noexcept : deleter_{deleter} {}
    void incrementSharedRefCounter() { sharedRefCounter_++; }
    void decrementSharedRefCounter() {
        if (sharedRefCounter_ > 0) {
            sharedRefCounter_--;
        }
    }
    std::size_t getSharedrefCounter() const { return sharedRefCounter_.load(); }

    void incrementWeakRefCounter() { weakRefCounter_++; }
    void decrementWeakRefCounter() {
        if (weakRefCounter_ > 0) {
            weakRefCounter_--;
        }
    }
    std::size_t getWeakRefCounter() const { return sharedRefCounter_.load(); }

    Deleter getDeleter() const { return deleter_; }

  private:
    std::atomic<std::size_t> weakRefCounter_ = 0;
    std::atomic<std::size_t> sharedRefCounter_ = 1;
    Deleter deleter_ = [](T *ptr) { delete ptr; };
};
} // namespace nostd
