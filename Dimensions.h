#pragma once

#include <string>
#include <sstream>

struct Dimensions {
    int width = 0;
    int height = 0;

    std::string ToString() const;
};
