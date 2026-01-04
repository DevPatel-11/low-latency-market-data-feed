#pragma once
#include "market_event.h"
#include <atomic>
#include <cstddef>
#include <array>
namespace mdf {
template<typename T, size_t Cap = 65536>
class LockFreeQueue {
    struct alignas(64) Slot { std::atomic<uint64_t> seq{0}; T data; };
    std::array<Slot, Cap> buf_;
    std::atomic<uint64_t> enq_{0}, deq_{0};
    static constexpr uint64_t MASK = Cap - 1;
public:
    bool try_enqueue(const T& v) {
        uint64_t pos = enq_.load(std::memory_order_acquire);
        if ((pos + 1) & MASK == deq_.load() & MASK) return false;
        buf_[pos & MASK].data = v;
        enq_.store(pos + 1, std::memory_order_release);
        return true;
    }
    bool try_dequeue(T& v) {
        uint64_t pos = deq_.load(std::memory_order_acquire);
        if (pos == enq_.load()) return false;
        v = buf_[pos & MASK].data;
        deq_.store(pos + 1, std::memory_order_release);
        return true;
    }
    size_t size() const { return enq_.load() - deq_.load(); }
};
}
