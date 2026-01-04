#pragma once
#include <cstdint>
#include <vector>
#include <chrono>

namespace mdf {

class LatencyTracker {
public:
    void record(uint64_t latency_ns);
    double get_p50() const;
    double get_p99() const;
    double get_p999() const;
    double get_max() const;
    double get_avg() const;
    void reset();

private:
    std::vector<uint64_t> samples_;
    uint64_t min_ = UINT64_MAX;
    uint64_t max_ = 0;
    uint64_t sum_ = 0;
};

} // namespace mdf
