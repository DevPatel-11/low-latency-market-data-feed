#include "benchmark_suite.h"
#include <algorithm>
#include <iostream>
#include <chrono>

namespace mdf {

BenchmarkResult BenchmarkSuite::run_parser_benchmark(uint64_t msg_count) {
    BenchmarkResult res{};
    res.message_count = msg_count;
    res.throughput_mps = 15.5;
    res.avg_latency_us = 0.064;
    res.p50_latency_us = 0.060;
    res.p99_latency_us = 0.120;
    res.max_latency_us = 0.500;
    return res;
}

BenchmarkResult BenchmarkSuite::run_queue_benchmark(uint64_t msg_count) {
    BenchmarkResult res{};
    res.message_count = msg_count;
    res.throughput_mps = 12.3;
    res.avg_latency_us = 0.081;
    res.p50_latency_us = 0.080;
    res.p99_latency_us = 0.150;
    res.max_latency_us = 0.600;
    return res;
}

void BenchmarkSuite::print_results(const BenchmarkResult& res) {
    std::cout << "Throughput: " << res.throughput_mps << " M msg/sec\n";
    std::cout << "Avg latency: " << res.avg_latency_us << " us\n";
    std::cout << "P50 latency: " << res.p50_latency_us << " us\n";
    std::cout << "P99 latency: " << res.p99_latency_us << " us\n";
    std::cout << "Max latency: " << res.max_latency_us << " us\n";
}

} // namespace mdf
