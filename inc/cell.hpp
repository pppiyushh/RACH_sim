#pragma once

#include <iostream>
#include <vector>

#include "channel.hpp"
#include "UE.hpp"


class Cell
{
    public:

    Cell(Channel *channel, std::uint64_t current_slot);
    void schedule_SSBs(Channel *channel, std::uint64_t current_slot);

    private:
    std::vector<UE> ue_list_;
    bool next_SSB_scheduled_ = false;
        
    // SSB will be sent after each 5 slot
    std::uint64_t SSB_frequency_in_slots = 5; 

   

};
