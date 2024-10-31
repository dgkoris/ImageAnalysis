#include <iomanip>
#include <iostream>
#include <vector>
#include "SharedMemoryReader.h"
#include "ImageDeserialiser.h"
#include "ImageData.h"
#include "Constants.h"

int main() {
    try {
        SharedMemoryReader sharedMemory(SHARED_MEMORY_NAME);
        ImageDeserialiser deserialiser(sharedMemory);

        int numberOfImages = deserialiser.ReadNumberOfImages();
        std::vector<ImageData> images;
        int totalImageSize = 0;

        for (int i = 0; i < numberOfImages; ++i) {
            ImageData data = deserialiser.ReadImageMetadata();
            totalImageSize += data.size;
            images.push_back(std::move(data));
        }

        for (const auto& data : images) {
            std::cout << data.ToString() << '\n';
        }

        std::cout << "\nTotal images: "
            << std::left << std::setw(25) << numberOfImages
            << std::right << std::setw(10) << totalImageSize << " bytes\n";

        std::wcout << L"\nData read from shared memory '" << SHARED_MEMORY_NAME << L"'.\n\n";
        std::cout << "Press Enter to exit...\n";
        std::cin.get();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
