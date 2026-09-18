#include "Saving.h"
#include <fstream>
#include <iostream>

Config::Config(const std::string& filename) : filename(filename) {}

Config::~Config() {
    save();
}

bool Config::load() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Could not open config file: " << filename << std::endl;
        return false;
    }

    std::string key;
    int value;
    while (file >> key >> value) {
        data[key] = value;
    }

    file.close();
    return true;
}

bool Config::save() {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Could not open config file for writing: " << filename << std::endl;
        return false;
    }

    for (const auto& pair : data) {
        file << pair.first << " " << pair.second << std::endl;
    }

    file.close();
    return true;
}

int Config::getInt(const std::string& key, int defaultValue) {
    if (data.find(key) != data.end()) {
        return data[key];
    }
    return defaultValue;
}

void Config::setInt(const std::string& key, int value) {
    data[key] = value;
}
