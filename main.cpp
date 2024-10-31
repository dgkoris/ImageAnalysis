#include <iostream>
#include "Constants.h"

int main() {
    try {
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
