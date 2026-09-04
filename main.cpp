#include <iostream>
#include <thread>
#include <barrier>

using namespace std;

#define MAX_SLOTS 100000000
std::barrier<> slot_barrier{3};

void ue_thread()
{
    cout << "UE thread\n";
    slot_barrier.arrive_and_wait();
}

void channel_thread()
{
    cout << "Channel thread\n";
    slot_barrier.arrive_and_wait();
}

void cell_thread()
{
    cout << "Cell thread\n";
    slot_barrier.arrive_and_wait();
}

int main() {
    cout << "Hello, World!" << endl;

    
    thread ue(ue_thread);
    thread channel(channel_thread);
    thread cell(cell_thread);

    

    auto start = std::chrono::high_resolution_clock::now();

    for(auto _slots = 0; _slots < MAX_SLOTS; _slots++) {
        
    }

    auto end = std::chrono::high_resolution_clock::now();

    auto us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Execution time: " << us.count() << " microseconds" << std::endl;

    ue.join();
    channel.join();
    cell.join();

    return 0;
}