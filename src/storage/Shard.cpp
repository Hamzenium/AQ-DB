#include "Shard.h"

std::string Shard::get(const std::string& key) {
    if (data.find(key) != data.end()) {
        return data[key];
    }
    return "";
}

void Shard::set(const std::string& key, const std::string& value) {
    data[key] = value;
}

bool Shard::del(const std::string &key) {
    return data.erase(key);
}
