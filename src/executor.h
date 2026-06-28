#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "command.h"
#include "storage.h"
#include <string>

class CommandExecutor {
public:
    CommandExecutor(StorageEngine& storage);

    std::string execute(const Command& command);

private:
    StorageEngine& storage;

    std::string executeSet(const Command& command);
    std::string executeGet(const Command& command);
    std::string executeDelete(const Command& command);
};

#endif // EXECUTOR_H
