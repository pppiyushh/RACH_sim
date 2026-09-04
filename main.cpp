#include <iostream>
#include <thread>
#include <barrier>
#include <cstdint>
#include <queue>
#include <vector>
#include "UE.hpp"

using namespace std;

#define MAX_SLOTS 51
std::barrier<> slot_barrier{3};

void ue_thread()
{
    UE ue(1, UeState::POWERED_OFF);
    cout << "UE thread\n";
    

    for(auto _slots = 0; _slots < MAX_SLOTS; _slots++) {
        if(MAX_SLOTS < 50)
        cout << "UE running slot: " << _slots << std::endl;
        slot_barrier.arrive_and_wait();
    }
}

void channel_thread()
{
    cout << "Channel thread\n";
    

    for(auto _slots = 0; _slots < MAX_SLOTS; _slots++) {
        if(MAX_SLOTS < 50)
        cout << "Channel running slot: " << _slots << std::endl;
        slot_barrier.arrive_and_wait();
    }
}

void cell_thread()
{
    cout << "Cell thread\n";

    for(auto _slots = 0; _slots < MAX_SLOTS; _slots++) {
        if(MAX_SLOTS < 50)
        cout << "Cell running slot: " << _slots << std::endl;
        slot_barrier.arrive_and_wait();
    }

    
}

int main() {
    cout << "Hello, World!" << endl;

    auto start = std::chrono::high_resolution_clock::now();
    thread ue(ue_thread);
    thread channel(channel_thread);
    thread cell(cell_thread);

    ue.join();
    channel.join();
    cell.join();

    auto end = std::chrono::high_resolution_clock::now();
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Execution time: " << us.count() << " microseconds" << std::endl;

    return 0;
}