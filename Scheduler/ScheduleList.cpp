#include "ScheduleList.h"
#include <iostream>
#include <iomanip>
#include <chrono>



void ScheduleList::create()
{
	Task task;
	task.updateTitle();
	task.updateDate();
	task.updateDescription();
	task.updateLocation();

	schedules.insert({ task.title, task });
}

ScheduleList::ScheduleList()
{
	const auto now = std::chrono::utc_clock::now();
	std::ostringstream oss;
	oss << std::format("{0:%F} {0:%R}", now);
	lastDate = oss.str();
}

void ScheduleList::read(std::ifstream& MyFile)
{
	std::string title, desc, date, place;
	getline(MyFile, lastDate);
	while (!MyFile.eof()) {
		getline(MyFile, title);
		getline(MyFile, date);
		getline(MyFile, desc);
		getline(MyFile, place);
		if (title == "" || title == "\n") return;
		schedules.insert({ title, Task(title, date, desc, place) });
	}
}

void ScheduleList::write(std::ofstream& file)
{
	const auto now = std::chrono::utc_clock::now();
	file << std::format("{0:%F} {0:%R}", now) << '\n';

	for (const auto& t : schedules) {
		file << t.second.title << '\n';
		file << t.second.date << '\n';
		file << t.second.description << '\n';
		file << t.second.location << '\n';
	}
}

void ScheduleList::remove(std::string title)
{
	auto [first, last] = schedules.equal_range(title);
	std::cout << schedules.count(title) << " matches found.\n";
	while (first != last) {
		first->second.read();
		std::cout << "\nRemove entry? y/n\n";
		char ch;
		do {
			std::cin >> ch;
			if (ch == 'y') {
				first = schedules.erase(first);
			}
			else {
				++first;
			}
		} while (ch != 'y' && ch != 'n');
	}
}

void ScheduleList::displayAll()
{
	for (const auto& t : schedules) {
		t.second.read();
		std::cout << '\n';
	}
}

void ScheduleList::displayToday()
{
	int count = 0;
	std::cout << "Todays tasks:\n";
	const auto now = std::chrono::utc_clock::now();
	std::ostringstream oss;
	oss << std::format("{0:%F}", now);
	auto str = oss.str();
	for (const auto& t : schedules) {
		if (str == t.second.date.substr(0, 10)) {
			t.second.read();
			++count;
			std::cout << "\n";
		}
	}
	if (count == 0) {
		std::cout << "none\n";
	}
}

void ScheduleList::displayUpcoming()
{
	int count = 0;
	std::cout << "Upcoming tasks:\n";
	const auto now = std::chrono::utc_clock::now();
	std::ostringstream oss;
	oss << std::format("{0:%F}", now);
	auto str = oss.str();
	for (const auto& t : schedules) {
		if (str < t.second.date.substr(0, 10)) {
			t.second.read();
			++count;
			std::cout << '\n';
		}
	}
	if (count == 0) {
		std::cout << "none\n\n";
	}
}

void ScheduleList::sinceLastRun()
{
	std::cout << "Tasks due since last execution of program\n";
	const auto now = std::chrono::utc_clock::now();
	std::ostringstream oss;
	oss << std::format("{0:%F} {0:%R}", now);
	int count = 0;
	for (const auto& t : schedules) {
		if (lastDate < t.second.date && t.second.date <= oss.str()) {
			++count;
			t.second.read();
		}
	}
	if (count == 0) {
		std::cout << "none\n";
	}
}

void ScheduleList::update(std::string title)
{
	auto [first, last] = schedules.equal_range(title);
	int count = schedules.count(title);
	std::cout << count << " matches found\n";
	while (first != last) {
		first->second.read();
		std::cout << "Update this entry? y/n\n";
		char ch;
		do {
			std::cin >> ch;
			if (ch == 'y') {
				first->second.updateTask();
			}
		} while (ch != 'y' && ch != 'n');
		if (first->first != first->second.title) {
			Task t = first->second;
			first = schedules.erase(first);
			schedules.insert({ t.title, t });
		}
		else {
			++first;
		}
	}
}

void ScheduleList::displayOne(std::string title)
{
	auto [first, last] = schedules.equal_range(title);
	int count = schedules.count(title);
	if (count != 1) {
		std::cout << count << " matches found.\n";
	}
	if (count == 1) {
		first->second.read();
		std::cout << '\n';
		return;
	}
	while (first != last) {
		std::cout << "\nTask schduled for " << first->second.date << " Display? y/n\n";
		char ch;
		do {
			std::cin >> ch;
			if (ch == 'y') {
				first->second.read();
			}
			++first;
		} while (ch != 'y' && ch != 'n');
	}
}
