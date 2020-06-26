#pragma once
#include <string>
#include <vector>

class Helper
{
public:
	/// Methods
	/**
	 *\brief: used to read and validate the user input
	 *\param low: the lower limit of acceptable input
	 *\param high: the higher limit of acceptable input
	 *\param charChoices: used when the input is to be compared
	 *						against some characters
	 */
	static int readChoice(int low, int high, std::string charChoices="");
	/**
	 * \brief: displays the vector of string in a menu style
	 * \param menuOptions the strings to be displayed
	 */
	static void displayMenu(const std::vector <std::string>& menuOptions);
	/**
	 * \brief : draws a line separator
	 * \param length : length of the line
	 */
	static void line(int length = 30);
	/**
	 * \brief draws a double line separator
	 * \param length :length of the line
	 */
	static void dLine(int length = 30);
	/**
	 * \brief :used to cause time delay
	 *		  causes thread sleep
	 * \param ms :time to delay in ms
	 */
	static void delay(int ms);
	/**
	 * \brief :display a string in style
	 * \param str :the string to display
	 */
	static void stringDisplay (std::string str);
};

