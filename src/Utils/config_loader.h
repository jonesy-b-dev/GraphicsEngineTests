#pragma once
#include <fstream>
#include <string>
#include <map>

class Config_loader
{
public:
	Config_loader(std::string file);
	// Get values from config
	float GetFloat(std::string section, std::string key);
	int	GetInt(std::string section, std::string key);
	bool GetBool(std::string section, std::string key);
	std::string GetString(std::string section, std::string key);
	
	// Set values in the config
	void WriteFloat(std::string, std::string key, float value);
	void WriteInt(std::string, std::string key, int value);
	void WriteBool(std::string, std::string key, bool value);
	void WriteString(std::string, std::string key, std::string value);

private:
	void GetValueErrorHander(std::string section, std::string key, std::string type, const std::exception& error);
	void GetValueErrorHander(std::string section, std::string key, std::string type);

private:
	std::ifstream m_configStream;
	std::map<std::string, std::map<std::string, std::string>> m_configData;
	std::string m_delimiter = "=";
};

