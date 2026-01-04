#pragma once

#include "market_event.h"
#include <string>
#include <thread>
#include <atomic>
#include <random>
#include <chrono>

namespace mdf {

class BinanceAdapter {
public:
    using EventCallback = std::function<void(const MarketEvent&)>;

    explicit BinanceAdapter(const std::string& symbol = "BTCUSDT");
    ~BinanceAdapter();

    void start(EventCallback cb);
    void stop();
    void reconnect();

    bool is_connected() const { return connected_; }
    uint64_t messages_received() const { return msg_count_; }

private:
    std::string symbol_;
    EventCallback callback_;
    std::thread reader_thread_;
    std::atomic<bool> connected_{false};
    std::atomic<bool> running_{false};
    uint64_t msg_count_ = 0;
    std::mt19937_64 gen_;

    MarketEvent parse_trade(const std::string& json);
    MarketEvent parse_depth(const std::string& json);
    void run_reader();
};

} // namespace mdf
