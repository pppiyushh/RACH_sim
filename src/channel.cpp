#include "channel.hpp"
#include "logging.hpp"

using namespace std;

Channel::Channel() {
    LOG << "Channel created" << std::endl;
}

Channel::~Channel() {
    LOG << "Channel destroyed" << std::endl;
}

bool Channel::supported_frequency_resource(std::uint32_t frequency_resource) const {
        // For demonstration, let's assume the channel supports frequency resources in the range [0, 99]
        return frequency_resource < 100;
    }

void Channel::schedule(
    Resource *resource,
    Payload *payload,
    std::uint64_t cur_slot
) {
    std::lock_guard<std::mutex> lock(schedule_mutex_);

    std::uint64_t slot = resource->first; 
    std::uint32_t frequency_resource = resource->second; 
    if(slot <= cur_slot) {
        LOG << "Error: Cannot schedule a message in the past. Current slot: " << cur_slot << ", Attempted slot: " << slot << std::endl;
        return;
    }
    schedule_.push({
    {slot, frequency_resource},
    *payload
});
    LOG << "Scheduled message of type " << static_cast<int>(payload->type)
         << " at slot " << slot
         << " on frequency resource " << frequency_resource
         << std::endl;
}

bool Channel::listen(std::uint64_t slot,
    std::uint32_t frequency_resource, 
    Payload *received,
    std::uint64_t cur_slot
) {
    std::lock_guard<std::mutex> lock(schedule_mutex_);

    if(cur_slot != slot) {
        LOG << "Error: Cannot listen to a future slot or Past slot. Current slot: " << cur_slot << ", Attempted slot: " << slot << std::endl;
        return false;
    }

    if (!schedule_.empty())
    {
        if(schedule_.top().first.first == slot && 
        schedule_.top().first.second == frequency_resource)
        {
            const auto& scheduled_item = schedule_.top();
            *received = scheduled_item.second;
            LOG << "Received message of type " << static_cast<int>(received->type)
                << " at slot " << slot
                << " on frequency resource " << frequency_resource
                << std::endl;
            return true;
        }
    }
    else 
    {
        LOG << "No message scheduled for slot " << slot
             << " on frequency resource " << frequency_resource
             << std::endl;
    }
    
    return false;
}
void Channel::deschedule_past_slots(std::uint64_t cur_slot) 
{
    std::lock_guard<std::mutex> lock(schedule_mutex_);

    while (!schedule_.empty() && 
        schedule_.top().first.first <= cur_slot) 
    {
        LOG << "Descheduling message of type " << static_cast<int>(schedule_.top().second.type)
             << " at slot " << schedule_.top().first.first
             << " on frequency resource " << schedule_.top().first.second
             << std::endl;
        schedule_.pop();
    }
}
