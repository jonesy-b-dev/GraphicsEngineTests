#pragma once
#include <fstream>
#include <string>
#include <map>

class Config_loader
{
public:
	Config_loader(const char* file);
	// Get values from config
	float GetFloat(const char* section, const char* key);
	int	GetInt(const char* section, const char* key);
	bool GetBool(const char* section, const char* key);
	std::string GetString(const char* section, const char* key);
	
	// Set values in the config
	void WriteFloat(const char* section, const char* key, float value);
	void WriteInt(const char* section, const char* key, int value);
	void WriteBool(const char* section, const char* key, bool value);
	void WriteString(const char* section, const char* key, const char* value);

private:
	void GetValueErrorHander(const char* section, const char* key, const char* type, const std::exception& error);
	void GetValueErrorHander(const char* section, const char* key, const char* type);

private:
	std::ifstream m_configStream;
	const char* m_file;
	std::map<std::string, std::map<std::string, std::string>> m_configData;
	std::string m_delimiter = "=";
};

