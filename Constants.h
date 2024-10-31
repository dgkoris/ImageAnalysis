#pragma once

#include <windows.h>

// Shared memory constants
constexpr wchar_t SHARED_MEMORY_NAME[] = L"Local\\SharedMemoryImages";  // Shared memory name
constexpr DWORD MAPPING_SIZE = 65536;                                   // Size of the shared memory mapping region
