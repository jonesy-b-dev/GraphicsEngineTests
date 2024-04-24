#include "config_loader.h"

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
