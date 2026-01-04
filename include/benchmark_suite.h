#pragma once
#include "market_event.h"
#include <cstdint>
#include <vector>

namespace mdf {

struct BenchmarkResult {
    uint64_t message_count;
    double throughput_mps;
    double avg_latency_us;
    double p50_latency_us;
    double p99_latency_us;
    double max_latency_us;
};

class BenchmarkSuite {
public:
    static BenchmarkResult run_parser_benchmark(
        uint64_t msg_count = 1000000);
    static BenchmarkResult run_queue_benchmark(
        uint64_t msg_count = 1000000);
    static void print_results(const BenchmarkResult& res);
};

} // namespace mdf
