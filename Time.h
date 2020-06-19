#pragma once
#include <windows.h>
#include <stdio.h>
#include <iostream>

class Time
{
	private:
		int hour;
		int minute;
		
	public:
		Time();
		Time(int hr, int m);
		static SYSTEMTIME lt;
		static int localHour;
		static int localMinute;
		void setTime(int, int);
		int getHour();
		int getMinute();
		std::pair<int, int> getTime();
		std::pair<int, int> getTimeDiff();
		static void calcLocalTime() {
				GetLocalTime(&lt);
				Time::localHour = lt.wHour;
				Time::localMinute = lt.wMinute;
		}
		friend bool operator > (const Time& lhs, const Time& rhs);
		friend  bool operator < (const Time& lhs, const Time& rhs);
		friend std::ostream& operator << (std::ostream& output, Time time);
};