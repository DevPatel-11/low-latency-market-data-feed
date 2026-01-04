#pragma once
#include "market_event.h"

namespace mdf {

class EventConsumer {
public:
    virtual ~EventConsumer() = default;
    virtual void on_event(const MarketEvent& evt) = 0;
    virtual void on_batch(const std::vector<MarketEvent>& events) = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
};

class SimpleConsumer : public EventConsumer {
public:
    void on_event(const MarketEvent& evt) override;
    void on_batch(const std::vector<MarketEvent>& events) override;
    void start() override { running_ = true; }
    void stop() override { running_ = false; }
    uint64_t processed_count() const { return count_; }

private:
    bool running_ = false;
    uint64_t count_ = 0;
};

} // namespace mdf
