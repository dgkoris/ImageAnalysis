#pragma once

#include <string>
#include <iomanip>
#include "Dimensions.h"

struct ImageData {
    int size = 0;
    std::string name;
    Dimensions dimensions;

    std::string ToString() const;
};
