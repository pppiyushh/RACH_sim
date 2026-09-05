#include "channel.hpp"
#include <iostream>

using namespace std;

Channel::Channel() {
    cout << "Channel created" << std::endl;
}

Channel::~Channel() {
    cout << "Channel destroyed" << std::endl;
}

bool Channel::supported_frequency_resource(std::uint32_t frequency_resource) const {
        // For demonstration, let's assume the channel supports frequency resources in the range [0, 99]
        return frequency_resource < 100;
    }

Channel::schedule(
    std::uint64_t slot, 
    std::uint32_t frequency_resource, 
    const Payload& payload, 
    uint64_t cur_slot
) {
    if(slot <= cur_slot) {
        cout << "Error: Cannot schedule a message in the past. Current slot: " << cur_slot << ", Attempted slot: " << slot << std::endl;
        return;
    }
    schedule_.push({
    {slot, frequency_resource},
    payload
});
    cout << "Scheduled message of type " << static_cast<int>(payload.type)
         << " at slot " << slot
         << " on frequency resource " << frequency_resource
         << std::endl;
}

Channel::listen(std::uint64_t slot, 
    std::uint32_t frequency_resource, 
    Payload& received,
    uint64_t cur_slot
) {
    if(cur_slot != slot) {
        cout << "Error: Cannot listen to a future slot or Past slot. Current slot: " << cur_slot << ", Attempted slot: " << slot << std::endl;
        return false;
    }

    if (!schedule_.empty())
    {
        if(schedule_.top().first.first == slot && 
        schedule_.top().first.second == frequency_resource)
        {
            const auto& scheduled_item = schedule_.top();
            received = scheduled_item.second;
            schedule_.pop();
            cout << "Received message of type " << static_cast<int>(received.type)
                << " at slot " << slot
                << " on frequency resource " << frequency_resource
                << std::endl;
            return true;
        }
    }
    else 
    {
        cout << "No message scheduled for slot " << slot
             << " on frequency resource " << frequency_resource
             << std::endl;
    }
    
    return false;
}