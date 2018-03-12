#pragma once
#include <time.h>
#include <iostream>
struct DateTime
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;

	static DateTime Now()
	{
		time_t theTime = time(0);
		tm *atm = new tm();
		localtime_s(atm, &theTime);
		DateTime dt;
		dt.year = atm->tm_year;
		dt.month = atm->tm_mon;
		dt.day = atm->tm_mday;
		dt.hour = atm->tm_hour;
		dt.minute = atm->tm_min;
		dt.second = atm->tm_sec;

		return dt;
	}

	static DateTime Today()
	{
		time_t theTime = time(0);
		tm *atm = new tm();
		localtime_s(atm, &theTime);
		DateTime dt;
		dt.year = atm->tm_year;
		dt.month = atm->tm_mon;
		dt.day = atm->tm_mday;

		return dt;
	}

	DateTime& operator=(const DateTime &arg)
	{
		if (this != &arg)
		{
			year = arg.year;
			month = arg.month;
			day = arg.day;
			hour = arg.hour;
			minute = arg.minute;
			second = arg.second;
		}
	}

	DateTime& operator-(const DateTime& other)
	{
		DateTime dt;
		dt.year = this->year - other.year;
		dt.month = this->month - other.month;
		dt.day = this->day - other.day;
		dt.hour = this->hour - other.hour;
		dt.minute = this->minute - other.minute;
		dt.second = this->second - other.second;

		return dt;
	}
	std::ostream& operator<<(std::ostream& os)
	{
		os << year << "/" << month << "/" << day << "T"
			<< hour << ":" << minute << ":" << second;
		// write obj to stream
		return os;
	}
	std::istream& operator>>(std::istream& is)
	{
		char dk;
		is >> year >> dk >> month >> dk >> day >> dk 
			>> hour >> dk >> minute >> dk >> second;

		return is;
	}
};