#pragma once
#include <cstdint>
namespace mdf {
enum class EventType : uint8_t { Trade = 0, AddOrder = 1, CancelOrder = 2, ModifyOrder = 3 };
struct MarketEvent {
    uint64_t timestamp_ns;
    uint32_t instrument_id;
    EventType type;
    uint64_t price;
    uint64_t quantity;
    uint8_t side;
    MarketEvent() = default;
    MarketEvent(uint64_t ts, uint32_t id, EventType et, uint64_t p, uint64_t q, uint8_t s)
        : timestamp_ns(ts), instrument_id(id), type(et), price(p), quantity(q), side(s) {}
};
}
