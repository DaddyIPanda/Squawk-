#pragma once

#include <string>
#include <unordered_map>

class Config {
public:
    Config(const std::string& filename);
    ~Config();

    bool load();
    bool save();

    int getInt(const std::string& key, int defaultValue = 0);
    void setInt(const std::string& key, int value);

private:
    std::string filename;
    std::unordered_map<std::string, int> data;
};
