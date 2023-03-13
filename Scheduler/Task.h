#pragma once
#include <string>
class Task
{
public:
	Task() = default;
	Task(std::string title, std::string date, std::string desc, std::string location) 
		: title(title), description(desc), date(date), location(location) {}
	void updateTitle();
	void updateDate();
	void updateDescription();
	void updateLocation();
	void updateTask();
	void read() const;
	friend class ScheduleList;
private:
	int getYear();
	int getMonth();
	void getDay(int year, int month);
	void getTime();
	std::string title{};
	std::string description{};
	std::string date{};
	std::string location{};
};

