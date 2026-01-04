#pragma once
#include "market_event.h"
#include <atomic>
#include <cstdint>

namespace mdf {

class BackpressureHandler {
public:
    explicit BackpressureHandler(uint64_t threshold);
    bool check_backpressure(uint64_t queue_size);
    void set_threshold(uint64_t threshold);
    uint64_t get_dropped_count() const { return dropped_; }
    void reset_stats();

private:
    uint64_t threshold_;
    std::atomic<uint64_t> dropped_{0};
};

class AdaptiveBatcher {
public:
    explicit AdaptiveBatcher(uint32_t max_batch_size = 1000);
    void add_event(const MarketEvent& evt);
    std::vector<MarketEvent> flush();
    uint32_t batch_size() const { return batch_.size(); }

private:
    uint32_t max_batch_size_;
    std::vector<MarketEvent> batch_;
};

} // namespace mdf
