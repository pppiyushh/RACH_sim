#pragma once

#include <cstdint>
#include <cstdlib>
#include <utility>

#define SSB_FREQ 0 // Example frequency resource for SSB

enum class MessageType {
    SSB,
    PRACH,
    RAR,
    MSG3,
    MSG4
};

using Resource = std::pair<std::uint64_t, std::uint32_t>; // Slot, Frequency/Channel


struct Payload {
    MessageType type;

    // SSB-specific for now
    std::uint16_t pci;
    std::uint8_t ssb_index;
};
using ScheduledItem =
    std::pair<Resource, Payload>;
    

struct SlotComparator {
    bool operator()(
        const ScheduledItem& lhs,
        const ScheduledItem& rhs
    ) const
    {
        return lhs.first.first > rhs.first.first;
    }
};

inline void get_future_resource(Resource *r)
{
    const std::uint64_t slot_offset = std::rand() % 5;
    const std::uint32_t frequency_resource = std::rand() % 100;

    r->first += slot_offset;
    r->second = frequency_resource;
}
