#include <iostream>

Cell::Cell() {
    std::cout << "Cell created" << std::endl;
    Cell.schedule_SSBs();
}

Cell::~Cell() {
    std::cout << "Cell destroyed" << std::endl;
}

Cell::schedule_SSBs() {
    return;
}