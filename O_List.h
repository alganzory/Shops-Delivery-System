#pragma once
#include <iosfwd>
#include <string>

class O_List
{
public:
	/// Members
	static std::string filePath;
	static std::fstream dataFile;
	
	/// Methods
	static void readFromFile();
	static void writeToFile();
};

