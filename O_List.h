#pragma once
#include <iosfwd>
#include <string>

class O_List
{
public:
	static std::string filePath;
	static std::fstream dataFile;
	
	static void readFromFile();
	static void writeToFile();
};

