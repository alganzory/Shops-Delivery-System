#pragma once
#include <iosfwd>
#include <string>

class O_List
{
	/// Members

private:
	
	static std::string filePath;
	static std::fstream dataFile;
	
public:

	/// Setters
	static void setFilePath(const char* fP);
	
	/// Methods
	static void readOrders();
	static void writeOrders();
};

