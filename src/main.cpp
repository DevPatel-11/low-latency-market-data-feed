#include "market_event.h"
#include "feed_parser.h"
#include "lock_free_queue.h"
#include <iostream>
#include <chrono>
#include <atomic>
#include <thread>
#include <cstring>
#include <random>

using namespace mdf;

int main(int argc, char* argv[]) {
    uint64_t duration = 5;
    if (argc > 1) duration = std::stoul(argv[1]);

    std::cout << "Low-Latency Market Data Feed Handler" << std::endl;
    std::cout << "Duration: " << duration << " seconds" << std::endl;

    std::atomic<uint64_t> event_count{0};
    std::atomic<bool> running{true};

    auto start_time = std::chrono::high_resolution_clock::now();
    auto end_time = start_time + std::chrono::seconds(duration);
    
    BinaryFeedParser parser;

    while (std::chrono::high_resolution_clock::now() < end_time) {
        uint8_t data[17];
        *(uint64_t*)data = event_count;
        *(uint32_t*)(data + 8) = 46000 * 10000;
        *(uint32_t*)(data + 12) = 1000;
        data[16] = 1;
        
        auto events = parser.parse(data, 17);
        event_count += events.size();
    }

    auto stop_time = std::chrono::high_resolution_clock::now();

    double elapsed = std::chrono::duration<double>(stop_time - start_time).count();
    double throughput = event_count / elapsed / 1e6;

    std::cout << "\nResults:" << std::endl;
    std::cout << "Events processed: " << event_count << std::endl;
    std::cout << "Elapsed time: " << elapsed << "s" << std::endl;
    std::cout << "Throughput: " << throughput << " M msg/sec" << std::endl;

    return 0;
}
