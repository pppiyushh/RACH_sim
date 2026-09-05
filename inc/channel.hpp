#pragma once

#include <cstdint>
#include <mutex>
#include <queue>
#include <vector>

#include "RadioTypes.hpp"

class Channel {
public:
    Channel();
    ~Channel();

    void schedule(
        Resource *resource,
        Payload *payload,
        std::uint64_t cur_slot
    );

    bool listen(
        std::uint64_t slot,
        std::uint32_t frequency_resource,
        Payload *received,
        uint64_t cur_slot
    );

    bool supported_frequency_resource(
        std::uint32_t frequency_resource
    ) const;

    void deschedule_past_slots(std::uint64_t cur_slot);

private:
    std::priority_queue<
        ScheduledItem,
        std::vector<ScheduledItem>,
        SlotComparator
    > schedule_;

    std::mutex schedule_mutex_;

    
};
