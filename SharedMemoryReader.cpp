#include "SharedMemoryReader.h"
#include <sstream>

SharedMemoryReader::SharedMemoryReader(const wchar_t* name) : name_(name) {
    hMapFile_ = OpenFileMapping(FILE_MAP_READ, FALSE, name_);
    if (!hMapFile_) {
        std::ostringstream oss;
        oss << "Couldn't read shared memory from the SharedMemoryManager project. (Error code: " << GetLastError() << ")\n\n"
            << "Please ensure that SharedMemoryManager is running and that BMP images are loaded into shared memory.\n\n";
        throw std::runtime_error(oss.str());
    }
}

SharedMemoryReader::~SharedMemoryReader() {
    CloseHandleSafe();
}

LPVOID SharedMemoryReader::MapMemory(DWORD offset, DWORD size) const {
    DWORD alignedOffset = (offset / MAPPING_SIZE) * MAPPING_SIZE; // Align the offset
    DWORD delta = offset - alignedOffset; // Calculate the delta from the aligned offset
    return MapViewOfFile(hMapFile_, FILE_MAP_READ, 0, alignedOffset, delta + size); // Map the memory
}

void SharedMemoryReader::UnmapMemory(LPVOID pBuf) const {
    UnmapViewOfFile(pBuf); // Unmap the specified memory
}

void SharedMemoryReader::CloseHandleSafe() {
    if (hMapFile_ && hMapFile_ != INVALID_HANDLE_VALUE) {
        CloseHandle(hMapFile_); // Close the handle
        hMapFile_ = nullptr; // Reset handle
    }
}
