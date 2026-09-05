#include "UE.hpp"
#include "logging.hpp"

using namespace std;

const char* to_string(UeState state)
{
    switch (state) {
        case UeState::POWERED_OFF:
            return "POWERED_OFF";

        case UeState::CELL_SEARCH:
            return "CELL_SEARCH";

        case UeState::SYSTEM_INFORMATION_ACQUIRED:
            return "SYSTEM_INFORMATION_ACQUIRED";

        case UeState::RACH_READY:
            return "RACH_READY";

        case UeState::WAITING_FOR_RAR:
            return "WAITING_FOR_RAR";

        case UeState::WAITING_FOR_CONTENTION_RESOLUTION:
            return "WAITING_FOR_CONTENTION_RESOLUTION";

        case UeState::CONNECTED:
            return "CONNECTED";

        case UeState::SSB_DETECTED:
            return "SSB_DETECTED";
    }

    return "UNKNOWN";
}

UE::UE(std::uint32_t ue_id, UeState initial_state)
    : ue_id_(ue_id),
      state_(initial_state)
{
    LOG << "UE " << ue_id_ << " created with initial state: " << to_string(initial_state) << std::endl;
}

bool UE::listen(Channel *c, Resource *resource, Payload *received, std::uint64_t cur_slot)
{
    // Implementation for listening to SSB
    if(resource->first != cur_slot) {
        LOG << "Error: Cannot listen to a future slot or Past slot. Current slot: " << cur_slot << ", Attempted slot: " << resource->first << std::endl;
        return false;
    }
    if(c->listen(resource->first, resource->second, received, cur_slot)) {
        LOG << "UE " << ue_id_ << " received message of type " << static_cast<int>(received->type)
             << " at slot " << resource->first
             << " on frequency resource " << resource->second
             << std::endl;
        return true;
    }
    return false;
}
