#include "feed_parser.h"
#include "lock_free_queue.h"
#include <iostream>
#include <thread>
#include <atomic>
using namespace mdf;
std::atomic<uint64_t> msg_count{0};
std::atomic<bool> running{true};
void producer(LockFreeQueue<MarketEvent>& q, size_t rate) {
    BinaryFeedParser p;
    uint32_t id = 0;
    while (running) {
        uint8_t msg[17];
        msg[0] = (id++ % 2 == 0) ? 1 : 2;
        *(uint32_t*)(msg + 1) = id % 100;
        *(uint64_t*)(msg + 5) = 50000 + (id % 1000);
        *(uint64_t*)(msg + 13) = 100 + (id % 500);
        auto evts = p.parse(msg, 17);
        for (auto& e : evts) {
            if (q.try_enqueue(e)) msg_count++;
        }
    }
}
void consumer(LockFreeQueue<MarketEvent>& q) {
    while (running) {
        MarketEvent e;
        while (q.try_dequeue(e));
        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
}
int main(int argc, char** argv) {
    size_t rate = argc > 1 ? std::atol(argv[1]) : 100000;
    size_t dur = argc > 2 ? std::atol(argv[2]) : 3;
    LockFreeQueue<MarketEvent> q;
    std::cout << "Feed handler: " << rate << " msg/sec for " << dur << "s\n";
    std::thread prod(producer, std::ref(q), rate);
    std::thread cons(consumer, std::ref(q));
    std::this_thread::sleep_for(std::chrono::seconds(dur));
    running = false;
    prod.join();
    cons.join();
    std::cout << "Processed: " << msg_count << " messages\n";
    return 0;
}
