#ifndef PARSER_H
#define PARSER_H

#include "command.h"
#include <string>
#include <vector>

class Parser {
public:
    Parser() = default;

    Command parse(const std::string& input);

private:
    Command parseSet(const std::vector<std::string>& tokens);
    Command parseGet(const std::vector<std::string>& tokens);
    Command parseDelete(const std::vector<std::string>& tokens);
    std::vector<std::string> tokenize(const std::string& input);
};

#endif // PARSER_H
