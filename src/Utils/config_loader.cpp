#include "config_loader.h"
#include <iostream>

Config_loader::Config_loader(std::string file)
{
    // Load the config file
    configStream.open(file);
    if (configStream.is_open())
        std::cout << "Config File open\n";
    else 
        std::cout << "Failed to open config file, file: " << file << "\n";

    std::string line;
    int lineNumber = 0;
    std::string currentSection = "not set";

    // Parse config
    try
    {
        // Loop over all the line
        while (std::getline(configStream, line))
        {
            lineNumber++;
            // Skip if line is empty
            if (line.empty()) continue;
            // Skip if line is a comment
            if (line[0] == ';') continue;
            // Set the current section if we find a [
            if (line[0] == '[')
            {
                size_t posStart = line.find("[");
                size_t posEnd = line.find("]");
                std::string sectionTmp = line;

                if (posStart != std::string::npos && posEnd != std::string::npos)
                {

                    sectionTmp.erase(posEnd, 1);
                    sectionTmp.erase(posStart, 1);
                }
                else
                {
                    std::cout << "Missing either \"[\" or \"]\" in on line " << lineNumber << "\n";
                }
                currentSection = sectionTmp;
            }
            // Get the value for the section
            if (line[0] != '[' && currentSection != "not set")
            {
                size_t pos = line.find(delimiter);

                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos + delimiter.length());

                //std::cout << "Section: " << currentSection << ",key: " << key << ",val: " << value << "\n";

                configData[currentSection][key] = value;

                //std::cout << configData[currentSection][key] << "\n";
            }
            else continue;

            // Print stuff for debugging
            //std::cout << currentSection << "\n";
            //std::cout << line << "\n";
        }
    }
    catch (const std::exception&)
    {
        std::cout << "Failed to parse config on line " << lineNumber << "\n";
    }
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
