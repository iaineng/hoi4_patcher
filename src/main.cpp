#include <iostream>
#include <filesystem>
#include "pattern_matcher.hpp"
#include "file_utils.hpp"

namespace fs = std::filesystem;

int main() {
    int exitCode = 0;
    try {
        if (!fs::exists("hoi4.exe")) {
            std::cerr << "Error: hoi4.exe not found in current directory\n";
            exitCode = 1;
            goto exit;
        }

        auto binaryData = readBinaryFile("hoi4.exe");
        if (binaryData.empty()) {
            std::cerr << "Error: Cannot open or read hoi4.exe\n";
            exitCode = 1;
            goto exit;
        }

        const std::string targetPattern = "85 C0 0F 94 C3 E8 ?? ?? ?? ?? 0F B6 D3 48 8B C8 E8 ?? ?? ?? ??";
        const auto matchLocations = findPatternInBinary(binaryData, parseHexPattern(targetPattern));

        if (matchLocations.empty()) {
            std::cout << "Pattern not found in file. Exiting...\n";
            exitCode = 1;
            goto exit;
        }

        if (matchLocations.size() > 1) {
            std::cout << "Error: Found multiple matches (" << matchLocations.size() << " locations). This is unsafe to patch.\n";
            exitCode = 1;
            goto exit;
        }

        std::cout << "Found pattern at offset: 0x" << std::hex << matchLocations[0] << std::dec << "\n";

        if (!backupFile("hoi4.exe", "hoi4.exe.bak")) {
            std::cerr << "Error: Failed to create backup file\n";
            exitCode = 1;
            goto exit;
        }

        binaryData[matchLocations[0]] = 0x31;
        binaryData[matchLocations[0] + 1] = 0xC0;

        if (!writeDataToFile("hoi4.exe", binaryData)) {
            std::cerr << "Error: Failed to write patched file\n";
            exitCode = 1;
            goto exit;
        }

        std::cout << "Successfully patched the file\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        exitCode = 1;
    }

exit:
    std::cout << "\nPress Enter to exit...\n";
    std::cin.get();
    return exitCode;
}
