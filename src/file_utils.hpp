#pragma once
#include <string>
#include <vector>
#include <cstdint>

bool writeDataToFile(const std::string& filepath, const std::vector<uint8_t>& data);
std::vector<uint8_t> readBinaryFile(const std::string& filepath);
bool backupFile(const std::string& sourceFile, const std::string& backupFile);
