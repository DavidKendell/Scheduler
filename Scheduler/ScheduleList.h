#pragma once
#include "Task.h"
#include <unordered_map>
#include <fstream>
class ScheduleList
{
public:
	void create();
	ScheduleList();
	void displayOne(std::string title);
	void displayAll();
	void displayToday();
	void displayUpcoming();
	void sinceLastRun();

	void update(std::string title);

	void remove(std::string title);
	
	void read(std::ifstream& file);
	void write(std::ofstream& file);
private:
	std::unordered_multimap<std::string, Task> schedules;
	std::string lastDate;
};


