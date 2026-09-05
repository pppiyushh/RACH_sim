#pragma once

#include <cstdint>
#include <utility>

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
        const Resource& lhs,
        const Resource& rhs
    ) const
    {
        return lhs.first > rhs.first;
    }
};