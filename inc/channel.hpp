#pragma once

#include <cstdint>
#include <queue>
#include <vector>

#include "RadioTypes.hpp"
#include "UE.hpp"   // temporary if Payload currently lives there

class Channel {
public:
    Channel();
    ~Channel();

    void schedule(
        std::uint64_t slot,
        std::uint32_t frequency_resource,
        const Payload& payload
    );

    bool listen(
        std::uint64_t slot,
        std::uint32_t frequency_resource,
        Payload& received
    );

    bool supported_frequency_resource(std::uint32_t frequency_resource) const {
        // For demonstration, let's assume the channel supports frequency resources in the range [0, 99]
        return frequency_resource < 100;
    }

private:
    std::priority_queue<
        ScheduledItem,
        std::vector<ScheduledItem>,
        SlotComparator
    > schedule_;

    
};