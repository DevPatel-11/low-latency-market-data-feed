#pragma once
#include "market_event.h"
#include <atomic>
#include <memory>
#include <cstring>

namespace mdf {

template<typename T>
class MPSCQueue {
public:
    explicit MPSCQueue(size_t capacity) : capacity_(capacity) {
        data_ = std::make_unique<T[]>(capacity);
    }
    
    bool try_enqueue(const T& item) {
        size_t pos = tail_.fetch_add(1, std::memory_order_relaxed);
        if (pos - head_.load(std::memory_order_acquire) >= capacity_) {
            tail_.fetch_sub(1, std::memory_order_relaxed);
            return false;
        }
        new (&data_[pos % capacity_]) T(item);
        return true;
    }
    
    bool try_dequeue(T& item) {
        size_t h = head_.load(std::memory_order_relaxed);
        if (h >= tail_.load(std::memory_order_acquire)) return false;
        item = data_[h % capacity_];
        head_.store(h + 1, std::memory_order_release);
        return true;
    }
    
    bool empty() const {
        return head_.load(std::memory_order_acquire) >= 
               tail_.load(std::memory_order_acquire);
    }

private:
    std::atomic<size_t> head_{0};
    std::atomic<size_t> tail_{0};
    size_t capacity_;
    std::unique_ptr<T[]> data_;
};

} // namespace mdf
