#ifndef LAB8_CONFIGURATIONS_H
#define LAB8_CONFIGURATIONS_H

#include <vector>

#define DAYS 5
#define GROUPS 5
#define CLASSES_PER_DAY 6

#define GENETIC_POPULATION_SIZE 10
#define GENETIC_GENERATIONS 1000

struct SubjectSpecs {
	std::string title;
	int classes_per_week;
};

const std::vector<SubjectSpecs> SUBJECTS = {
		{.title = "Object Oriented Programming", .classes_per_week=1},
		{.title = "Database Management", .classes_per_week=1},
		{.title = "Operating Systems", .classes_per_week=1},
		{.title = "Computer System Architecture", .classes_per_week=1},
		{.title = "Software Engineering", .classes_per_week=1},
		{.title = "Graph Algorithms", .classes_per_week=1},
		{.title = "Data Structures and Algorithms", .classes_per_week=1},
		{.title = "Parallel and Distributed Systems", .classes_per_week=1},
};

const std::vector<std::string> WEEKDAYS = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

// ease of use
using DayTimetable_t = std::vector<SubjectSpecs>;
using GroupTimetable_t = std::vector<DayTimetable_t>;
using FullTimetable_t = std::vector<GroupTimetable_t>;

#endif //LAB8_CONFIGURATIONS_H
