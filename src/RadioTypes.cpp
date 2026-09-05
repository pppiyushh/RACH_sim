#include <random>

void get_future_resource(Resource *r)
{
    std::uint64_t slot = rand() % 3;
    std::uint32_t frequency_resource = rand() % 100; // Random frequency resource for demonstration

    r->first = r.first + slot; +
    r->second = frequency_resource;
}
