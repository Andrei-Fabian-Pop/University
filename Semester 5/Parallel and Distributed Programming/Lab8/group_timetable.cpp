#include "group_timetable.h"
#include <utility>
#include <iostream>
#include <iomanip>

GroupTimetable::GroupTimetable(std::string name, GroupTimetable_t timetable) : m_name(std::move(name)),
																			   m_timeTable(timetable) {

}

GroupTimetable::GroupTimetable(std::string name, std::vector<int> linerized_timetable) : m_name(name) {
	for (int i = 0; i < linerized_timetable.size() / CLASSES_PER_DAY; ++i) {
		DayTimetable_t table;

		for (int j = 0; j < CLASSES_PER_DAY; ++j) {
			int index = linerized_timetable[i * CLASSES_PER_DAY + j];
			if (index < 0) {
				table.push_back({
					.title = "Free time",
					.classes_per_week = 0
				});
			} else {
				table.push_back({
					.title = SUBJECTS[index].title,
					.classes_per_week = SUBJECTS[index].classes_per_week
				});
			}
		}

		m_timeTable.push_back(table);
	}
}

GroupTimetable_t GroupTimetable::getTimeTable() {
	return m_timeTable;
}

void GroupTimetable::setGroupTable(GroupTimetable_t groupTimetable) {
	m_timeTable = groupTimetable;
}

void GroupTimetable::print_group_table() {
	std::string title = "Class " + m_name + " |";
	std::cout << std::setw(20) << title;
	for (int i = 0; i < DAYS; ++i) {
		std::cout << std::setw(37) << WEEKDAYS[i] + " |";
	}
	std::cout << std::endl;

	// Print the timetable
	for (int period = 0; period < CLASSES_PER_DAY; ++period) {
		std::cout << std::setw(20) << "Period " + std::to_string(period + 1) + " |";
		for (int day = 0; day < DAYS; ++day) {
			const SubjectSpecs& subject = m_timeTable[day][period];
			std::cout << std::setw(37) << subject.title + " |";
		}
		std::cout << std::endl;
	}
}
