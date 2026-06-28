#include "parser.h"
#include <sstream>
#include <algorithm>
#include <cctype>

std::vector<std::string> Parser::tokenize(const std::string& input) {
    std::vector<std::string> tokens;
    std::istringstream iss(input);
    std::string token;

    while (iss >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

Command Parser::parseSet(const std::vector<std::string>& tokens) {
    if (tokens.size() < 3) {
        return Command(CommandType::UNKNOWN);
    }

    std::string key = tokens[1];
    std::string value = tokens[2];

    return Command(CommandType::SET, key, value);
}

Command Parser::parseGet(const std::vector<std::string>& tokens) {
    if (tokens.size() < 2) {
        return Command(CommandType::UNKNOWN);
    }

    std::string key = tokens[1];
    return Command(CommandType::GET, key, "");
}

Command Parser::parseDelete(const std::vector<std::string>& tokens) {
    if (tokens.size() < 2) {
        return Command(CommandType::UNKNOWN);
    }

    std::string key = tokens[1];
    return Command(CommandType::DELETE, key, "");
}

Command Parser::parse(const std::string& input) {
    std::vector<std::string> tokens = tokenize(input);

    if (tokens.empty()) {
        return Command(CommandType::UNKNOWN);
    }

    std::string command = tokens[0];
    
    // Convert to uppercase for comparison
    std::transform(command.begin(), command.end(), command.begin(),
                   [](unsigned char c) { return std::toupper(c); });

    if (command == "SET") {
        return parseSet(tokens);
    } else if (command == "GET") {
        return parseGet(tokens);
    } else if (command == "DELETE") {
        return parseDelete(tokens);
    } else {
        return Command(CommandType::UNKNOWN);
    }
}
