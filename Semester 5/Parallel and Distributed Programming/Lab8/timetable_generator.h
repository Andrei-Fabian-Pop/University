#ifndef LAB8_TIMETABLE_GENERATOR_H
#define LAB8_TIMETABLE_GENERATOR_H

#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iomanip>

#include "configurations.h"
#include "group_timetable.h"

class TimetableGenerator {
public:
	explicit TimetableGenerator();

	[[maybe_unused]] std::vector<GroupTimetable> getTimetables();
	void printTimetables();

private:
	using matrix_t = std::vector<std::vector<int>>;

	void geneticAlgorithm(int totalPeriods, int studentGroups, int populationSize, int generations);
	static int getRandomItem(std::vector<int>& vec);
	matrix_t initializeTimetable(int totalPeriods, int studentGroups);
	static int fitness(const matrix_t& timetable);
	static matrix_t crossover(const matrix_t& parent1, const matrix_t& parent2);
	static void mutate(matrix_t& board);

	std::vector<int> m_subjectIndexes;
	std::vector<GroupTimetable> m_timeTables;
};


#endif //LAB8_TIMETABLE_GENERATOR_H