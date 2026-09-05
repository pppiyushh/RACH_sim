#include <iostream>
#include "cell.hpp"
#include "RadioTypes.hpp"
#include "logging.hpp"



Cell::Cell(Channel *channel, std::uint64_t current_slot) {
    LOG << "Cell created" << std::endl;
    schedule_SSBs(channel, current_slot);
}

void Cell::schedule_SSBs(Channel *channel, std::uint64_t current_slot) {

    Resource resource{};
    resource.first = current_slot;
    get_future_resource(&resource);
    resource.second = SSB_FREQ; // Example frequency resource for SSB
    Payload payload{MessageType::SSB, 0, 0}; // Example payload for SSB
    channel->schedule(
        &resource, // Schedule SSBs in the future
        &payload, // Example payload for SSB
        current_slot
    );
    LOG << "Current slot: " << current_slot << std::endl;
    LOG << "Cell scheduled SSB at slot: " << resource.first
         << " on frequency resource: " << resource.second
         << std::endl;
    return;
}
