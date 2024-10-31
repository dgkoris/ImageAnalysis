#pragma once

#include "SharedMemoryReader.h"
#include "ImageData.h"

class ImageDeserialiser {
public:
    explicit ImageDeserialiser(const SharedMemoryReader& reader);

    int ReadNumberOfImages();
    ImageData ReadImageMetadata();

private:
    const SharedMemoryReader& reader_;
    int currentOffset_ = 0;
};
