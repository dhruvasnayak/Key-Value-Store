#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <unordered_map>
#include <optional>

class StorageEngine {
public:
    StorageEngine() = default;

    void set(const std::string& key, const std::string& value);

    std::optional<std::string> get(const std::string& key) const;

    bool remove(const std::string& key);

    void clear();

    size_t size() const;

private:
    std::unordered_map<std::string, std::string> store;
};

#endif // STORAGE_H
