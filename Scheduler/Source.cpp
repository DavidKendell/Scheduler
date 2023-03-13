#include <iostream>
#include "Task.h"
#include "ScheduleList.h"
#include <fstream>

void PrintMenu() {
	std::cout << "1 Create new task\n";
	std::cout << "2 View a task\n";
	std::cout << "3 View all tasks\n";
	std::cout << "4 View upcoming tasks\n";
	std::cout << "5 View today's tasks\n";
	std::cout << "6 Update a task\n";
	std::cout << "7 Delete a task\n";
	std::cout << "8 View tasks due since last program execution\n";
	std::cout << "q quit\n";
}
void ExecuteMenu(ScheduleList& tasks, char ch) {
	switch (ch) {
	case '1':
		tasks.create();
		break;
	case '2': {
		std::string title;
		std::cout << "Enter title\n";
		std::cin.ignore();
		getline(std::cin, title);
		tasks.displayOne(title);
		break;
	}
	case '3':
		tasks.displayAll();
		break;
	case '4':
		tasks.displayUpcoming();
		break;
	case '5':
		tasks.displayToday();
		break;
	case '6': {
		std::string title;
		std::cout << "Enter title of task to update\n";
		std::cin.ignore();
		getline(std::cin, title);
		tasks.update(title);
		break;
	}
	case '7': {
		std::cout << "Enter title of task to delete\n";
		std::string title;
		std::cin.ignore();
		getline(std::cin, title);
		tasks.remove(title);
	}
	case '8':
		tasks.sinceLastRun();
		break;
	}

}

int main() {
	ScheduleList tasks;
	{
		std::ifstream tasksFile("tasks.txt");
		if (tasksFile.good()) {
			tasks.read(tasksFile);
		}
	}
	char ch;
	PrintMenu();
	do {
		std::string choices = "12345678";
		std::cout << "Enter choice\n";
		std::cin >> ch;
		if (choices.find(ch) == std::string::npos && ch != 'q') {
			std::cout << "Invalid choice\n";
			continue;
		}
		ExecuteMenu(tasks, ch);
		PrintMenu();
	} while (ch != 'q');
	


	{
		std::remove("tasks.txt");
		std::ofstream tasksFile("tasks.txt");
		tasks.write(tasksFile);
	}
	


	
	
}


