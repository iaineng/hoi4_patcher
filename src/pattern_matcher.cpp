#include "pattern_matcher.hpp"

PatternMatcher::PatternMatcher(const std::vector<int>& searchPattern)
    : pattern(searchPattern)
    , patternLength(searchPattern.size()) {
}

std::vector<size_t> PatternMatcher::findAll(const std::vector<uint8_t>& data) const {
    std::vector<size_t> matches;
    if (patternLength == 0 || data.size() < patternLength) {
        return matches;
    }

    for (size_t pos = 0; pos <= data.size() - patternLength; ++pos) {
        bool matched = true;
        for (size_t i = 0; i < patternLength; ++i) {
            if (pattern[i] != -1 && data[pos + i] != static_cast<uint8_t>(pattern[i])) {
                matched = false;
                break;
            }
        }
        if (matched) {
            matches.push_back(pos);
        }
    }

    return matches;
}

std::vector<int> parseHexPattern(const std::string& pattern) {
    std::vector<int> bytes;
    std::string currentHexByte;
    
    for (const char c : pattern) {
        if (c == ' ') {
            if (!currentHexByte.empty()) {
                bytes.push_back(currentHexByte == "??" ? -1 : std::stoi(currentHexByte, nullptr, 16));
                currentHexByte.clear();
            }
        } else {
            currentHexByte += c;
        }
    }
    
    if (!currentHexByte.empty()) {
        bytes.push_back(currentHexByte == "??" ? -1 : std::stoi(currentHexByte, nullptr, 16));
    }
    
    return bytes;
}

std::vector<size_t> findPatternInBinary(const std::vector<uint8_t>& binaryData, const std::vector<int>& searchPattern) {
    const PatternMatcher matcher(searchPattern);
    return matcher.findAll(binaryData);
}
