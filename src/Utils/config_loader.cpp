#include "config_loader.h"
#include <iostream>

Config_loader::Config_loader(std::string file)
{
    configStream.open(file);
    if (configStream.is_open())
        std::cout << "Config File open\n";
    else 
        std::cout << "Failed to open config file, file: " << file << "\n";
}

float Config_loader::GetFloat(std::string section, std::string key)
{
    return 0.0f;
}

int Config_loader::GetInt(std::string section, std::string key)
{
    return 0;
}

bool Config_loader::GetBool(std::string section, std::string key)
{
    return false;
}

std::string Config_loader::GetString(std::string section, std::string key)
{
    return std::string();
}

void Config_loader::WriteFloat(std::string, std::string key, float value)
{
}

void Config_loader::WriteInt(std::string, std::string key, int value)
{
}

void Config_loader::WriteBool(std::string, std::string key, bool value)
{
}

void Config_loader::WriteString(std::string, std::string key, std::string value)
{
}
