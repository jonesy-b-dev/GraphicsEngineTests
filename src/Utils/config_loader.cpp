#include "config_loader.h"
#include <iostream>

Config_loader::Config_loader(const char* file)
{
    m_file = file;  
    // Load the config file
    m_configStream.open(file);
    if (m_configStream.is_open())
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
        while (std::getline(m_configStream, line))
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
                size_t pos = line.find(m_delimiter);

                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos + m_delimiter.length());

                //std::cout << "Section: " << currentSection << ",key: " << key << ",val: " << value << "\n";

                m_configData[currentSection][key] = value;

                //std::cout << m_configData[currentSection][key] << "\n";
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

float Config_loader::GetFloat(const char* section, const char* key)
{
    try
    {
        return std::stof(m_configData[section][key]);
    }
    catch(const std::exception& error)
    {
        GetValueErrorHander(section, key, "float", error);
        return 0;
    }
}

int Config_loader::GetInt(const char* section, const char* key)
{
    try
    {
        return std::stoi(m_configData[section][key]);
    }
    catch (const std::exception& error)
    {
        GetValueErrorHander(section, key, "int", error);
        return 0;
    }
}

bool Config_loader::GetBool(const char* section, const char* key)
{
    if(m_configData[section][key] == "true") return true;
    else if(m_configData[section][key] == "false") return false;

    else GetValueErrorHander(section, key, "bool");
        
    return 0;
}

std::string Config_loader::GetString(const char* section, const char* key)
{
    try
    {
        return m_configData[section][key];
    }
    catch (const std::exception& error)
    {
        GetValueErrorHander(section, key, "string", error);
        return 0;
    }
}

void Config_loader::WriteFloat(const char* section, const char* key, float value)
{

}

void Config_loader::WriteInt(const char* section, const char* key, int value)
{
}

void Config_loader::WriteBool(const char* section, const char* key, bool value)
{
}

void Config_loader::WriteString(const char* section, const char* key, const char* value)
{
}

void Config_loader::GetValueErrorHander(const char* section, const char* key, const char* type, const std::exception& error)
{
    std::cerr << error.what() << "\n";
    std::cout << "\nERROR: Failed to get config with type: " << type << " check the config for errors. \n"
        << "Failed config: [" << section  << "]" << key << "\n"
        << "Value: " << m_configData[section][key] << "\n";
}

void Config_loader::GetValueErrorHander(const char* section, const char* key, const char* type)
{
    std::cout << "\nERROR: Failed to get config with type: " << type << " check the config for errors. \n"
        << "Failed config: [" << section  << "]" << key << "\n"
        << "Value: " << m_configData[section][key] << "\n";
}
