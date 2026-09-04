#pragma once

#include <cstdint>
#include <queue>
#include <utility>

struct Payload {
    MessageType type;
    std::uint32_t frequency_resource;

    // SSB-specific for now
    std::uint16_t pci;
    std::uint8_t ssb_index;
};

using ScheduledItem = std::pair<std::uint64_t, Payload>;

struct SlotComparator {
    bool operator()(
        const ScheduledItem& lhs,
        const ScheduledItem& rhs
    ) const
    {
        return lhs.first > rhs.first;
    }
};
enum class MessageType {
    SSB,
    PRACH,
    RAR,
    MSG3,
    MSG4
};

enum class UeState {
    POWERED_OFF,
    CELL_SEARCH,
    SSB_DETECTED,
    SYSTEM_INFORMATION_ACQUIRED,
    RACH_READY,
    WAITING_FOR_RAR,
    WAITING_FOR_CONTENTION_RESOLUTION,
    CONNECTED
};


class UE {
public:
    UE(std::uint32_t ue_id,
    UeState initial_state = UeState::POWERED_OFF);

    void run_slot(std::uint64_t slot);

    void enqueue_tx(std::uint64_t slot, std::uint32_t frequency_resource);

    void enqueue_rx(std::uint64_t slot, std::uint32_t frequency_resource);

private:
    void listen(std::uint64_t slot);

    /*
      UE stores which slots to transmit on 
      Slot, Frequency/Channel
    */
    std::priority_queue<
    ScheduledItem,
    std::vector<ScheduledItem>,
    SlotComparator> tx_queue_;

    /*
      UE stores which slots to listen on 
      Slot, Frequency/Channel
    */
    std::priority_queue<
    ScheduledItem,
    std::vector<ScheduledItem>,
    SlotComparator> rx_schedule_;

    std::uint32_t ue_id_;
    UeState state_;
};