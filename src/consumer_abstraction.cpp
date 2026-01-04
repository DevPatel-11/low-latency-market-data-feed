#include "consumer_abstraction.h"

namespace mdf {

void SimpleConsumer::on_event(const MarketEvent& evt) {
    if (running_) count_++;
}

void SimpleConsumer::on_batch(const std::vector<MarketEvent>& events) {
    if (running_) count_ += events.size();
}

} // namespace mdf
