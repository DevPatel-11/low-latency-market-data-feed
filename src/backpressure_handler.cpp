#include "backpressure_handler.h"

namespace mdf {

BackpressureHandler::BackpressureHandler(uint64_t threshold)
    : threshold_(threshold) {}

bool BackpressureHandler::check_backpressure(uint64_t queue_size) {
    if (queue_size >= threshold_) {
        dropped_++;
        return true;
    }
    return false;
}

void BackpressureHandler::set_threshold(uint64_t threshold) {
    threshold_ = threshold;
}

void BackpressureHandler::reset_stats() {
    dropped_ = 0;
}

AdaptiveBatcher::AdaptiveBatcher(uint32_t max_batch_size)
    : max_batch_size_(max_batch_size) {}

void AdaptiveBatcher::add_event(const MarketEvent& evt) {
    batch_.push_back(evt);
}

std::vector<MarketEvent> AdaptiveBatcher::flush() {
    auto result = batch_;
    batch_.clear();
    return result;
}

} // namespace mdf
