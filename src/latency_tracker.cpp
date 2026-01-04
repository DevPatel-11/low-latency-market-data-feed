#include "latency_tracker.h"
#include <algorithm>
#include <cmath>

namespace mdf {

void LatencyTracker::record(uint64_t latency_ns) {
    samples_.push_back(latency_ns);
    min_ = std::min(min_, latency_ns);
    max_ = std::max(max_, latency_ns);
    sum_ += latency_ns;
}

double LatencyTracker::get_p50() const {
    if (samples_.empty()) return 0;
    auto sorted = samples_;
    std::sort(sorted.begin(), sorted.end());
    return sorted[sorted.size() / 2] / 1000.0;
}

double LatencyTracker::get_p99() const {
    if (samples_.empty()) return 0;
    auto sorted = samples_;
    std::sort(sorted.begin(), sorted.end());
    return sorted[sorted.size() * 99 / 100] / 1000.0;
}

double LatencyTracker::get_p999() const {
    if (samples_.empty()) return 0;
    auto sorted = samples_;
    std::sort(sorted.begin(), sorted.end());
    return sorted[sorted.size() * 999 / 1000] / 1000.0;
}

double LatencyTracker::get_max() const {
    return max_ / 1000.0;
}

double LatencyTracker::get_avg() const {
    if (samples_.empty()) return 0;
    return sum_ / samples_.size() / 1000.0;
}

void LatencyTracker::reset() {
    samples_.clear();
    min_ = UINT64_MAX;
    max_ = 0;
    sum_ = 0;
}

} // namespace mdf
