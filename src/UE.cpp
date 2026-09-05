#include "UE.hpp"
#include <iostream>

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
    cout << "UE " << ue_id_ << " created with initial state: " << to_string(initial_state) << std::endl;
}
