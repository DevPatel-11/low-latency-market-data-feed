#include "feed_parser.h"
#include "lock_free_queue.h"
#include <iostream>
#include <thread>
#include <atomic>
using namespace mdf;
std::atomic<uint64_t> msg_count{0}, running{1};
void producer(LockFreeQueue<MarketEvent>& q) {
    BinaryFeedParser p;
    for (uint32_t id = 0; running; id++) {
        uint8_t m[17];
        m[0] = (id % 2)? 1 : 2;
        *(uint32_t*)(m + 1) = id % 50;
        *(uint64_t*)(m + 5) = 50000 + (id % 1000);
        *(uint64_t*)(m + 13) = 100 + (id % 500);
        auto e = p.parse(m, 17);
        if (!e.empty() && q.try_enqueue(e[0])) msg_count++;
    }
}
void consumer(LockFreeQueue<MarketEvent>& q) {
    while (running) {
        MarketEvent e;
        while (q.try_dequeue(e));
        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
}
int main(int a, char** v) {
    size_t r = a > 1 ? atol(v[1]) : 100000;
    size_t d = a > 2 ? atol(v[2]) : 2;
    LockFreeQueue<MarketEvent> q;
    std::cout << "Handler: " << r << " msg/sec, " << d << "s\n";
    auto t0 = std::chrono::high_resolution_clock::now();
    std::thread prod(producer, std::ref(q));
    std::thread cons(consumer, std::ref(q));
    std::this_thread::sleep_for(std::chrono::seconds(d));
    running = 0;
    prod.join(); cons.join();
    auto dt = std::chrono::duration_cast<std::chrono::seconds>
        (std::chrono::high_resolution_clock::now() - t0).count();
    std::cout << "Processed: " << msg_count << " msgs in " << dt << "s\n";
}
