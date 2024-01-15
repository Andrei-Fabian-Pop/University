#ifndef LAB8_TIMETABLE_GENERATOR_DISTRIBUTED_H
#define LAB8_TIMETABLE_GENERATOR_DISTRIBUTED_H

#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <mpi/mpi.h>

#include "configurations.h"
#include "group_timetable.h"

class TimetableGeneratorDistributed {
public:
	explicit TimetableGeneratorDistributed();

	std::vector<GroupTimetable> getTimetables();
	void printTimetables();

private:
	using matrix_t = std::vector<std::vector<int>>;

	std::vector<int> m_subjectIndexes;  // list of subject IDs
	std::vector<GroupTimetable> m_timeTables;  // list of timetables for each group

	int m_procSize, m_rank;

	void geneticAlgorithm(int classesPerDay, int studentGroups, int populationSize, int generations);
	static int getRandomItem(std::vector<int>& vec);
	matrix_t initializeTimetable(int totalPeriods, int studentGroups);
	static int fitness(const matrix_t& timetable);

	static matrix_t crossover(const matrix_t& parent1, const matrix_t& parent2);

	static void mutate(matrix_t& board);
};


#endif //LAB8_TIMETABLE_GENERATOR_DISTRIBUTED_H
