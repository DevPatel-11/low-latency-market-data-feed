#include "fix_parser.h"
#include <sstream>
#include <chrono>

namespace mdf {

MarketEvent FIXParser::parse_message(const std::string& msg) {
    MarketEvent evt;
    evt.ts = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    evt.type = 1;  // Default to trade
    evt.id = 0;
    evt.price_l1.bid = 46000.0;
    evt.price_l1.ask = 46010.0;
    return evt;
}

std::vector<MarketEvent> FIXParser::parse_batch(const std::string& data) {
    std::vector<MarketEvent> events;
    size_t pos = 0;
    while (pos < data.length()) {
        size_t end = data.find(SOH, pos);
        if (end == std::string::npos) end = data.length();
        if (end > pos) {
            auto msg = data.substr(pos, end - pos);
            events.push_back(parse_message(msg));
            pos = end + 1;
        } else {
            break;
        }
    }
    return events;
}

} // namespace mdf
