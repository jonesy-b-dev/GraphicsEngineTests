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
                // store the position of the first and last character 
                size_t posStart = line.find("[");
                size_t posEnd = line.find("]");
                std::string sectionTmp = line;

                // First check if the characters were found and then remove the [ ] characters
                // so we have a clean value to store in $currentSection
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
                // Store the position of the delimiter ( = )
                size_t pos = line.find(m_delimiter);

                // store the key and value in a temp string
                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos + m_delimiter.length());

                //std::cout << "Section: " << currentSection << ",key: " << key << ",val: " << value << "\n";
                    
                // Store the values in the map
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

//
// GETTING CONFIGS
//
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

//
// WRITING CONFIGS
//
void Config_loader::WriteFloat(const char* section, const char* key, float value)
{
    m_configData[section][key] = std::to_string(value);

    std::ofstream configFile(m_file);

    if (!configFile.is_open())
    {
        std::cout << "Failed to open config file for writing float.\n" <<
            "Config to edit: [" << section << "]" << key << " = " << value << std::endl;
        return;
    }

    for (const auto& section : m_configData) 
    {
        configFile << "[" << section.first << "]\n";
        for (const auto& keyValue : section.second) 
        {
            configFile << keyValue.first << "=" << keyValue.second << "\n";
        }

        configFile << "\n"; // Add a blank line between sections
    }
    // Close file
    configFile.close();
}

void Config_loader::WriteInt(const char* section, const char* key, int value)
{
    m_configData[section][key] = std::to_string(value);

    std::ofstream configFile(m_file);

    if (!configFile.is_open())
    {
        std::cout << "Failed to open config file for writing int.\n" <<
            "Config to edit: [" << section << "]" << key << " = " << value << std::endl;
        return;
    }

    for (const auto& section : m_configData) 
    {
        configFile << "[" << section.first << "]\n";
        for (const auto& keyValue : section.second) 
        {
            configFile << keyValue.first << "=" << keyValue.second << "\n";
        }

        configFile << "\n"; // Add a blank line between sections
    }
    // Close file
    configFile.close();
}

void Config_loader::WriteBool(const char* section, const char* key, bool value)
{
    m_configData[section][key] = std::to_string(value);

    std::ofstream configFile(m_file);

    if (!configFile.is_open())
    {
        std::cout << "Failed to open config file for writing bool.\n" <<
            "Config to edit: [" << section << "]" << key << " = " << value << std::endl;
        return;
    }

    for (const auto& section : m_configData) 
    {
        configFile << "[" << section.first << "]\n";
        for (const auto& keyValue : section.second) 
        {
            configFile << keyValue.first << "=" << keyValue.second << "\n";
        }

        configFile << "\n"; // Add a blank line between sections
    }
    // Close file
    configFile.close();
}

void Config_loader::WriteString(const char* section, const char* key, const char* value)
{
    m_configData[section][key] = value;

    std::ofstream configFile(m_file);

    if (!configFile.is_open())
    {
        std::cout << "Failed to open config file for writing string.\n" <<
            "Config to edit: [" << section << "]" << key << " = " << value << std::endl;
        return;
    }

    for (const auto& section : m_configData) 
    {
        configFile << "[" << section.first << "]\n";
        for (const auto& keyValue : section.second) 
        {
            configFile << keyValue.first << "=" << keyValue.second << "\n";
        }

        configFile << "\n"; // Add a blank line between sections
    }
    // Close file
    configFile.close();
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
