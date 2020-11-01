#pragma once

#include <atomic>

constexpr std::size_t defaultRefCounterValue = 0;
constexpr std::size_t resetRefCounterValue = 1;

namespace nostd {
class CounterBlock {
  public:
    CounterBlock() : sharedRefCounter_(defaultRefCounterValue) {}
    CounterBlock(const CounterBlock &other) = delete;
    CounterBlock(CounterBlock &&other) = delete;

    CounterBlock &operator=(const CounterBlock &other) = delete;
    CounterBlock &operator=(CounterBlock &&other) = delete;

    ~CounterBlock() {}

    void incrementRefCounter() { sharedRefCounter_++; }
    void decrementRefCounter() { sharedRefCounter_--; }

    std::size_t getSharedrefCounter() const { return sharedRefCounter_.load(); }
    void resetRefCounter() { sharedRefCounter_ = resetRefCounterValue; }

  private:
    std::atomic<std::size_t> sharedRefCounter_ = 0;
};
} // namespace nostd
