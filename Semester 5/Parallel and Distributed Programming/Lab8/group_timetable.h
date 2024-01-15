#ifndef LAB8_GROUP_TIMETABLE_H
#define LAB8_GROUP_TIMETABLE_H

#include <string>
#include "configurations.h"

class GroupTimetable {
public:
	explicit GroupTimetable(std::string name, GroupTimetable_t timetable);
	explicit GroupTimetable(std::string name, std::vector<int> linerized_timetable);

	GroupTimetable_t getTimeTable();
	void setGroupTable(GroupTimetable_t groupTimetable);

	void print_group_table();

private:
	std::string m_name;
	GroupTimetable_t m_timeTable;
};


#endif //LAB8_GROUP_TIMETABLE_H
