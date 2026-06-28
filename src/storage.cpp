#include "storage.h"

void StorageEngine::set(const std::string& key, const std::string& value) {
    store[key] = value;
}

std::optional<std::string> StorageEngine::get(const std::string& key) const {
    auto it = store.find(key);
    if (it != store.end()) {
        return it->second;
    }
    return std::nullopt;
}

bool StorageEngine::remove(const std::string& key) {
    auto it = store.find(key);
    if (it != store.end()) {
        store.erase(it);
        return true;
    }
    return false;
}

void StorageEngine::clear() {
    store.clear();
}

size_t StorageEngine::size() const {
    return store.size();
}
