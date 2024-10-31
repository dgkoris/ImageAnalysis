#include "ImageData.h"
#include <sstream>

std::string ImageData::ToString() const {
    std::ostringstream oss;
    oss << "Loaded image: " << std::left << std::setw(25) << name
        << std::right << std::setw(10) << size << " bytes    "
        << dimensions.ToString();
    return oss.str();
}
