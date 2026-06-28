#include "executor.h"

CommandExecutor::CommandExecutor(StorageEngine& storage) 
    : storage(storage) {}

std::string CommandExecutor::executeSet(const Command& command) {
    if (command.key.empty()) {
        return "ERROR Invalid Command";
    }
    storage.set(command.key, command.value);
    return "OK";
}

std::string CommandExecutor::executeGet(const Command& command) {
    if (command.key.empty()) {
        return "ERROR Invalid Command";
    }
    auto value = storage.get(command.key);
    if (value.has_value()) {
        return value.value();
    } else {
        return "NOT_FOUND";
    }
}

std::string CommandExecutor::executeDelete(const Command& command) {
    if (command.key.empty()) {
        return "ERROR Invalid Command";
    }
    if (storage.remove(command.key)) {
        return "DELETED";
    } else {
        return "NOT_FOUND";
    }
}

std::string CommandExecutor::execute(const Command& command) {
    switch (command.type) {
        case CommandType::SET:
            return executeSet(command);
        case CommandType::GET:
            return executeGet(command);
        case CommandType::DELETE:
            return executeDelete(command);
        default:
            return "ERROR Unknown Command";
    }
}
