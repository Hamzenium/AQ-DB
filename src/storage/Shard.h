#ifndef SHARD_H
#define SHARD_H
#include <string>
#include <unordered_map>

class Shard {
public:
    std::string get(const std::string& key);
    void set(const std::string& key, const std::string& value);
    bool del(const std::string& key);

private:
    std::unordered_map<std::string, std::string> data;

#endif // SHARD_H



};