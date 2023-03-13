#include "Task.h"
#include <iostream>
#include <chrono>

void Task::updateTitle()
{
	std::cout << "Enter title (must not be blank):\n";
	std::cin.ignore();
	do {
		getline(std::cin, title);
	} while (title.find_first_not_of(" \t\n\v\f\r") == std::string::npos);
}

void Task::updateDate()
{
	int year = getYear();
	int month = getMonth();
	getDay(year, month);
	getTime();
}

void Task::updateDescription()
{
	std::cout << "Enter a brief description:\n";
	std::cin.ignore();
	getline(std::cin, description);
}

void Task::updateLocation()
{
	std::cout << "Enter location:\n";
	std::cin.ignore();
	getline(std::cin, location);
}

void Task::updateTask()
{
	char ch;
	do {
		std::cout << "Update title? y/n\n";
		std::cin >> ch;
		if (ch == 'y') {
			updateTitle();
		}
	} while (ch != 'y' && ch != 'n');
	do {
		std::cout << "Update date? y/n\n";
		std::cin >> ch;
		if (ch == 'y') {
			updateDate();
		}
	} while (ch != 'y' && ch != 'n');
	do {
		std::cout << "Update description? y/n\n";
		std::cin >> ch;
		if (ch == 'y') {
			updateDescription();
		}
	} while (ch != 'y' && ch != 'n');
	do {
		std::cout << "Update location? y/n\n";
		std::cin >> ch;
		if (ch == 'y') {
			updateLocation();
		}
	} while (ch != 'y' && ch != 'n');
}



void Task::read() const
{
	std::cout << "Title: " << title << '\n';
	std::cout << "Date: " << date << '\n';
	if (description != "") {
		std::cout << "Description: " << description << '\n';
	}
	if (location != "") {
		std::cout << "Location: " << location << '\n';
	}
}


int Task::getYear() {
	int year;
	char ch{};
	do {
		std::cout << "Enter year\n";
		std::cin >> year;
		if (std::cin.fail() || year <= 2000 || year > 9999) {
			std::cout << "Please enter a valid number\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			continue;
		}
		std::cout << "You have chosen: " << year << ". Is this correct? y/n\n";

		do {
			std::cin >> ch;
		} while (ch != 'y' && ch != 'n');
	} while (ch != 'y');
	date += std::to_string(year) + '-';
	return year;
}

int Task::getMonth() {
	int month;
	char ch{};
	do {
		std::cout << "Enter month: 1 = January, 2 = February etc...\n";
		std::cin >> month;
		if (std::cin.fail() || month <= 0 || month > 12) {
			std::cout << "Please enter a valid number\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			continue;
		}
		std::chrono::month m(month);
		std::cout << "You have chosen: " << std::format("{0:%B}", m) << ". Is this correct? y/n\n";

		do {
			std::cin >> ch;
		} while (ch != 'y' && ch != 'n');
	} while (ch != 'y');
	if (month < 10) {
		date += '0';
	}
	date += std::to_string(month) + '-';
	return month;
}
void Task::getDay(int year, int month) {
	int day;
	int upperBound;
	char ch = 0;
	if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0) && month == 2) {
		upperBound = 29;
	}
	else if (month == 2) {
		upperBound = 28;
	}
	else if ((month % 2 == 1 && month < 8) || (month % 2 == 0 && month >= 8)) {
		upperBound = 31;
	}
	else {
		upperBound = 30;
	}
	do {
		std::cout << "Enter the day\n";
		std::cin >> day;
		if (std::cin.fail() || day <= 0 || day > upperBound) {
			std::cout << "Please enter a valid number\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			continue;
		}
		std::chrono::year y(year);
		std::chrono::month m(month);
		std::chrono::day d(day);
		std::chrono::year_month_day ymd(y, m, d);
		std::cout << "You have chosen: " << day << ", which is a "
			<< std::format("{0:%A}", ymd) << ". Is this correct? y/n\n";
		do {
			std::cin >> ch;
		} while (ch != 'y' && ch != 'n');
	} while (ch != 'y');
	if (day < 10) {
		date += '0';
	}
	date += std::to_string(day) + ' ';
}
void Task::getTime() {
	int hour, minute;
	char ch{};
	do {
		std::cout << "Enter hour (0 - 23)\n";
		std::cin >> hour;
		std::cout << "Enter minute (0 - 59)\n";
		std::cin >> minute;

		if (std::cin.fail() || hour < 0 || hour > 23 || minute < 0 || minute > 59) {
			std::cout << "Please enter a valid values\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			continue;
		}
		std::cout << "You have chosen: " << std::setfill('0') << std::setw(2) << hour << ':'
			<< std::setfill('0') << std::setw(2) << minute
			<< ". Is this correct? y/n\n";

		do {
			std::cin >> ch;
		} while (ch != 'y' && ch != 'n');
	} while (ch != 'y');
	if (hour < 10) {
		date += '0';
	}
	date += std::to_string(hour) + ':';
	if (minute < 10) {
		date += '0';
	}
	date += std::to_string(minute);
}
