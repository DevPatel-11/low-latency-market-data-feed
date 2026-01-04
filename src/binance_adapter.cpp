#include "binance_adapter.h"
#include <iostream>
#include <chrono>

namespace mdf {

BinanceAdapter::BinanceAdapter(const std::string& symbol)
    : symbol_(symbol), gen_(std::random_device{}()) {}

BinanceAdapter::~BinanceAdapter() {
    stop();
}

void BinanceAdapter::start(EventCallback cb) {
    callback_ = cb;
    connected_ = true;
    running_ = true;
    reader_thread_ = std::thread(&BinanceAdapter::run_reader, this);
}

void BinanceAdapter::stop() {
    running_ = false;
    connected_ = false;
    if (reader_thread_.joinable()) {
        reader_thread_.join();
    }
}

void BinanceAdapter::reconnect() {
    if (!running_) return;
    connected_ = true;
}

MarketEvent BinanceAdapter::parse_trade(const std::string& json) {
    MarketEvent evt;
    evt.ts = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    evt.type = 1;
    evt.id = msg_count_++;
    std::uniform_real_distribution<> dist(45000.0, 47000.0);
    evt.price_l1.bid = dist(gen_);
    evt.price_l1.ask = evt.price_l1.bid + 10;
    return evt;
}

MarketEvent BinanceAdapter::parse_depth(const std::string& json) {
    MarketEvent evt;
    evt.ts = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    evt.type = 2;
    evt.id = msg_count_++;
    std::uniform_real_distribution<> dist(45000.0, 47000.0);
    evt.price_l1.bid = dist(gen_);
    evt.price_l1.ask = evt.price_l1.bid + 10;
    return evt;
}

void BinanceAdapter::run_reader() {
    std::uniform_int_distribution<> msg_type(0, 1);
    std::uniform_int_distribution<> sleep_us(100, 500);
    while (running_) {
        if (!connected_) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }
        MarketEvent evt = (msg_type(gen_) == 0) ?
            parse_trade("") : parse_depth("");
        if (callback_) callback_(evt);
        std::this_thread::sleep_for(std::chrono::microseconds(sleep_us(gen_)));
    }
}

} // namespace mdf
