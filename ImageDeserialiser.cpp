#include "ImageDeserialiser.h"
#include <cstring>

// Constants for metadata indices
constexpr int NUM_METADATA_INTS = 4;        // Total number of integers in metadata
constexpr int MAX_IMAGE_NAME_LENGTH = 256;  // Maximum length for image names

// Indices for metadata fields
constexpr int SIZE_INDEX = 0;               // Index for size
constexpr int WIDTH_INDEX = 1;              // Index for width
constexpr int HEIGHT_INDEX = 2;             // Index for height
constexpr int NAME_LENGTH_INDEX = 3;        // Index for name length
constexpr int NAME_DATA_INDEX = 4;          // Index for name data

ImageDeserialiser::ImageDeserialiser(const SharedMemoryReader& reader)
    : reader_(reader), currentOffset_(0) {}

int ImageDeserialiser::ReadNumberOfImages() {
    LPVOID pBuf = reader_.MapMemory(currentOffset_, sizeof(int));
    int numberOfImages;
    std::memcpy(&numberOfImages, pBuf, sizeof(int));
    reader_.UnmapMemory(pBuf);
    currentOffset_ += sizeof(int);
    return numberOfImages;
}

ImageData ImageDeserialiser::ReadImageMetadata() {
    ImageData data;

    // Map memory to read metadata for an image
    LPVOID pBuf = reader_.MapMemory(currentOffset_, (NUM_METADATA_INTS * sizeof(int)) + MAX_IMAGE_NAME_LENGTH);
    int delta = currentOffset_ % MAPPING_SIZE;

    // Read metadata fields using defined indices
    std::memcpy(&data.size, (char*)pBuf + delta + SIZE_INDEX * sizeof(int), sizeof(int));
    std::memcpy(&data.dimensions.width, (char*)pBuf + delta + WIDTH_INDEX * sizeof(int), sizeof(int));
    std::memcpy(&data.dimensions.height, (char*)pBuf + delta + HEIGHT_INDEX * sizeof(int), sizeof(int));

    // Read the length of the name and then the name itself
    int nameLength;
    std::memcpy(&nameLength, (char*)pBuf + delta + NAME_LENGTH_INDEX * sizeof(int), sizeof(int));
    data.name.resize(nameLength);
    std::memcpy(data.name.data(), (char*)pBuf + delta + NAME_DATA_INDEX * sizeof(int), nameLength);

    reader_.UnmapMemory(pBuf); // Unmap the memory after reading
    currentOffset_ += (NUM_METADATA_INTS * sizeof(int)) + nameLength; // Update the current offset

    return data;
}
