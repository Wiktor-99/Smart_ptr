#pragma once

#include <atomic>
#include <functional>


constexpr std::size_t defaultRefCounterValue = 1;

namespace nostd {
template<typename T>
class CounterBlock {

  public:
    using Deleter = std::function<void(T *)>;

  public:
    CounterBlock(Deleter deleter = [](T *ptr) { delete ptr; }) : deleter_{deleter},sharedRefCounter_{defaultRefCounterValue} {}
    CounterBlock(const CounterBlock &other) = delete;
    CounterBlock(CounterBlock &&other) = delete;

    CounterBlock &operator=(const CounterBlock &other) = delete;
    CounterBlock &operator=(CounterBlock &&other) = delete;

    ~CounterBlock() {}

    void incrementRefCounter() { sharedRefCounter_++; }
    void decrementRefCounter() { sharedRefCounter_--; }

    std::size_t getSharedrefCounter() const { return sharedRefCounter_.load(); }
    Deleter getDeleter()const {return deleter_;}
  private:
    std::atomic<std::size_t> sharedRefCounter_ = defaultRefCounterValue;
    Deleter deleter_ = [](T *ptr) { delete ptr; };
};
} // namespace nostd
