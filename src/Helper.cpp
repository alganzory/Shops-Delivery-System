#include "../include/Helper.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <sstream>
#include <string>

/// Methods
int Helper::readChoice(int low, int high, std::string charChoices)
{
	std::string input{};
	int choice{};
	char choiceChar;
	bool isChar = false;
	while (true)
	{
		getline(std::cin, input);

		// This code converts from string to number safely.
		std::stringstream inputStream(input);

		if (isalpha(input[0]) && input.size() ==1) { isChar = true; break; }
		if ((inputStream >> choice)) { isChar = false; break; }
		
		std::cout << "Invalid input, please try again" << std::endl;
	}
	
	if (isChar )
	{
		if (charChoices.find(input) != std::string::npos) return input[0];
		else std::cout << "Enter a choice from the ones shown: ";
		return readChoice(low, high, charChoices);
	}
	
	if (choice <= high && choice >= low) return choice;
	
	std::cout << "Enter a choice from " << low << " to " << high << ": ";
 	return readChoice(low, high,charChoices);
}

void Helper::displayMenu(const std::vector <std::string>& menuOptions)
{
	int counter = 0;
	for (const auto& option : menuOptions)
	{
	//	delay(100);
		std::cout << ++counter << "- " << option << std::endl;
	}

}

void Helper::line(int length)
{
	for (int i=0; i<length; i++)
	{
	//	if (i <= 50) delay(5);
	//	else delay(2);
		std::cout << '-';
	}
	std::cout << '\n';
}
void Helper::dLine(int length)
{
	for (int i = 0; i < length; i++)
	{
	//	if (i <= 50) delay(5);
		//else delay(2);
		std::cout << '=';
	}
	std::cout << '\n';
}

void Helper:: delay(int ms) {

	using namespace std::chrono;
	using namespace std::this_thread;
	sleep_until(system_clock::now() + milliseconds(ms));
}

void  Helper:: stringDisplay(std::string str)
{
	//for (auto character : str)
	//{
	////delay(50);
	//	std::cout << character;
	//}

	std::cout << str;
}

void Helper::dPrint(const std::string& str, int ms)
{
	std::cout << str;
}
