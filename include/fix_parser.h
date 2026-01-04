#pragma once
#include "market_event.h"
#include <string>
#include <vector>

namespace mdf {

class FIXParser {
public:
    static constexpr const char* VERSION = "4.2";
    
    MarketEvent parse_message(const std::string& msg);
    std::vector<MarketEvent> parse_batch(const std::string& data);
    
private:
    static const char SOH = 0x01;
};

} // namespace mdf
