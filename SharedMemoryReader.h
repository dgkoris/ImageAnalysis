#pragma once

#include <windows.h>
#include <string>
#include <optional>
#include <stdexcept>
#include "Constants.h"

class SharedMemoryReader {
public:
    explicit SharedMemoryReader(const wchar_t* name);
    ~SharedMemoryReader();

    LPVOID MapMemory(DWORD offset, DWORD size) const;
    void UnmapMemory(LPVOID pBuf) const;

private:
    HANDLE hMapFile_;
    const wchar_t* name_;

    void CloseHandleSafe();
};
