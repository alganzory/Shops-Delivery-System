#pragma once
#include <windows.h>
#include <iostream>

class Time
{
	/// Members
private:
	int hour;
	int minute;

public:
	/**
	 * \brief : the current time of system
	 */
	static SYSTEMTIME lt;
	static int localHour;
	static int localMinute;

public:
	/// Constructors
	Time();
	Time(int hr, int m);

	/// Getters
	int getHour();
	int getMinute();
	std::pair<int, int> getTime();
	/**
	 * \brief: get the time difference
				with the local time
	 * \return: pair of hour and minute
	 */
	std::pair<int, int> getTimeDiff();

	/// Setters
	void setTime(int, int);
	/**
	 * \brief : read current system time
	 *			into localHour and localMinute
	 */
	static void calcLocalTime();

	/// Operator
	/**
	 * \brief : compare the time
	 * \param lhs : time to compare and see whether it is later
	 * \param rhs : time to compare and see whether it is earlier
	 * \return : the boolean value of the comparation
	 */
	friend bool operator >(const Time& lhs, const Time& rhs);
	friend bool operator <(const Time& lhs, const Time& rhs);
	bool operator ==(const Time& rhs);
	/**
	 * \brief: display string of the time
	 * \param output : display
	 * \param time : the time to display
	 * \return : the display of string of the time
	 */
	friend std::ostream& operator <<(std::ostream& output, Time time);
};
