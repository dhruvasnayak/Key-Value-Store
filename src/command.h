#ifndef COMMAND_H
#define COMMAND_H

#include <string>

enum class CommandType {
    SET,
    GET,
    DELETE,
    UNKNOWN
};

class Command {
public:
    CommandType type;
    std::string key;
    std::string value;

    Command(CommandType t = CommandType::UNKNOWN, 
            const std::string& k = "", 
            const std::string& v = "")
        : type(t), key(k), value(v) {}
};

#endif // COMMAND_H
