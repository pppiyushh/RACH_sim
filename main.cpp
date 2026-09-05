#include <iostream>
#include <thread>
#include <barrier>
#include <cstdint>
#include <queue>
#include <vector>
#include "UE.hpp"
#include "channel.hpp"
#include "cell.hpp"
#include "logging.hpp"

using namespace std;

#define MAX_SLOTS 49
std::barrier<> slot_barrier{3};

Channel nr_sub6;
Channel nr_mmw;

void ue_thread()
{
    auto _slots = 0;
    UE ue(1, UeState::POWERED_OFF);

    for(_slots = 0; _slots < MAX_SLOTS; _slots++) 
    {
        LOG << "UE running slot: " << _slots << std::endl;

        /*Read SSB on every slot*/
        if(ue.state_ == UeState::CELL_SEARCH || ue.state_ == UeState::POWERED_OFF) 
        {
            Resource resource{_slots, SSB_FREQ};
            Payload received{};
            if(ue.listen(&nr_sub6, &resource, &received, _slots)) 
            {
                LOG << "UE detected SSB at slot: " << resource.first << " on frequency resource: " << resource.second << std::endl;
            }
            else
            {
                LOG << "UE did not detect SSB at slot: " << resource.first << " on frequency resource: " << resource.second << std::endl;
            }
        }
        slot_barrier.arrive_and_wait();
    }
}

void channel_thread()
{
    std::uint64_t _slots = 0;    
    Cell cell1(&nr_sub6, _slots);

    for(_slots = 0; _slots < MAX_SLOTS; _slots++) {

        if(_slots % 5 == 4) {
            cell1.schedule_SSBs(&nr_sub6, _slots);
        }
        slot_barrier.arrive_and_wait();
    }
}

void cell_thread()
{
    LOG << "Cell thread\n";

    for(auto _slots = 0; _slots < MAX_SLOTS; _slots++) {

        slot_barrier.arrive_and_wait();
    }
}

int main() {
    LOG << "Lets simulate RACH, shall we?\n";

    auto start = std::chrono::high_resolution_clock::now();
    thread ue(ue_thread);
    thread channel(channel_thread);
    thread cell(cell_thread);

    ue.join();
    channel.join();
    cell.join();

    auto end = std::chrono::high_resolution_clock::now();
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    LOG << "Execution time: " << us.count() << " microseconds" << std::endl;

    return 0;
}
