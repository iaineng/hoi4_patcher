#pragma once
#include <vector>
#include <cstdint>
#include <string>

class PatternMatcher {
public:
    explicit PatternMatcher(const std::vector<int>& searchPattern);
    std::vector<size_t> findAll(const std::vector<uint8_t>& data) const;

private:
    std::vector<int> pattern;
    size_t patternLength;
};

std::vector<int> parseHexPattern(const std::string& pattern);
std::vector<size_t> findPatternInBinary(const std::vector<uint8_t>& binaryData, const std::vector<int>& searchPattern);
