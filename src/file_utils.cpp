#include "file_utils.hpp"
#include <filesystem>
#include <fstream>
#include <limits>

namespace fs = std::filesystem;

bool writeDataToFile(const std::string& filepath, const std::vector<uint8_t>& data) {
    std::ofstream file(filepath, std::ios::binary);
    if (!file) return false;

    if (data.size() > static_cast<size_t>(std::numeric_limits<std::streamsize>::max())) {
        return false;
    }

    file.write(reinterpret_cast<const char*>(data.data()), 
               static_cast<std::streamsize>(data.size()));
    return file.good();
}

std::vector<uint8_t> readBinaryFile(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file) return {};
    
    return {std::istreambuf_iterator<char>(file),
            std::istreambuf_iterator<char>()};
}

bool backupFile(const std::string& sourceFile, const std::string& backupFile) {
    try {
        copy_file(sourceFile, backupFile, fs::copy_options::overwrite_existing);
        return true;
    } catch (const std::exception&) {
        return false;
    }
}
