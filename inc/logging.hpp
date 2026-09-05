#pragma once

#include <iostream>

#define LOG \
    (std::cout << "[" << __FILE__ << ":" << __LINE__ << "] ")
