#pragma once
#include "market_event.h"
#include <vector>
namespace mdf {
class BinaryFeedParser {
public:
    std::vector<MarketEvent> parse(const uint8_t* data, size_t len);
};
}
