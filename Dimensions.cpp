#include "Dimensions.h"

std::string Dimensions::ToString() const {
    std::ostringstream oss;
    oss << "(" << width << "x" << height << ")";
    return oss.str();
}
