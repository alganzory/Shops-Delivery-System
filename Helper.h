#pragma once
#include <string>
#include <vector>

class Helper
{
public:
	static int readChoice(int low, int high, std::string charChoices="");
	static void displayMenu(const std::vector <std::string>& menuOptions);
	static void line(int length = 30);
	static void dLine(int length = 30);
};

