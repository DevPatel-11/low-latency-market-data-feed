#include "feed_parser.h"
#include <chrono>
namespace mdf {
std::vector<MarketEvent> BinaryFeedParser::parse(const uint8_t* data, size_t len) {
    std::vector<MarketEvent> events;
    if (len < 17) return events;
    uint8_t type = data[0];
    uint32_t id = *(uint32_t*)(data + 1);
    uint64_t price = *(uint64_t*)(data + 5);
    uint64_t qty = *(uint64_t*)(data + 13);
    auto ts = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    events.emplace_back(ts, id, (type == 1) ? EventType::Trade : EventType::AddOrder, price, qty, 0);
    return events;
}
}
