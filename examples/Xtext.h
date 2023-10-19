#include <string>
#include <vector>
#include <sstream>

std::vector<std::string> splitText(const std::string& text, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream tokenStream(text);
    std::string token;
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}