#include "timetable_generator.h"

#define FREE_TIME (-1)

TimetableGenerator::TimetableGenerator() {
	for (int i = 0; i < SUBJECTS.size(); ++i) {
		for (int j = 0; j < SUBJECTS[i].classes_per_week; ++j) {
			m_subjectIndexes.push_back(i);
		}
	}

	TimetableGenerator::geneticAlgorithm(CLASSES_PER_DAY * DAYS,
										 GROUPS,
										 GENETIC_POPULATION_SIZE,
										 GENETIC_GENERATIONS);
}

[[maybe_unused]] std::vector<GroupTimetable> TimetableGenerator::getTimetables() {
	return m_timeTables;
}

void TimetableGenerator::printTimetables() {
	for (auto table: m_timeTables) {
		table.print_group_table();
		std::cout << "\n";
	}
}

void TimetableGenerator::geneticAlgorithm(int totalPeriods, int studentGroups, int populationSize,
										  int generations) {
	std::vector<matrix_t> population;

	// Initialize population
	population.reserve(populationSize);
	for (int i = 0; i < populationSize; ++i) {
		population.push_back(TimetableGenerator::initializeTimetable(totalPeriods, studentGroups));
	}

	for (int generation = 0; generation < generations; ++generation) {
		sort(population.begin(), population.end(), [](const auto& a, const auto& b) {
			return TimetableGenerator::fitness(a) < TimetableGenerator::fitness(b);
		});

		if (TimetableGenerator::fitness(population[0]) == 0) {
			std::cout << "Solution found in generation " << generation << std::endl;
			for (int i = 0; i < population[0].size(); ++i) {
				m_timeTables.emplace_back("Group " + std::to_string(i), population[0][i]);
			}
			return;
		}

		// Select top 50% of the population as parents
		std::vector<matrix_t> parents(population.begin(), population.begin() + populationSize / 2);

		// Create new generation through crossover and mutation
		std::vector<matrix_t> offspring;
		while (offspring.size() < populationSize - parents.size()) {
			size_t index1 = random() % parents.size();
			size_t index2 = random() % parents.size();
			matrix_t child = crossover(parents[index1], parents[index2]);

			if (random() % 100 < 20) {  // 20% chance of mutation
				TimetableGenerator::mutate(child);
			}

			offspring.push_back(child);
		}

		// Combine parents and offspring for the next generation
		population = parents;
		population.insert(population.end(), offspring.begin(), offspring.end());
	}

	std::cout << "No solution found." << std::endl;
}

int TimetableGenerator::getRandomItem(std::vector<int>& vec) {
	if (vec.empty()) {
		return FREE_TIME;
	}

	std::size_t index = random() % vec.size();
	int value = vec[index];
	vec.erase(vec.begin() + (long) (index));

	return value;
}

TimetableGenerator::matrix_t
TimetableGenerator::initializeTimetable(int totalPeriods, int studentGroups) {
	matrix_t timetable;
	for (int i = 0; i < studentGroups; ++i) {
		std::vector<int> group;
		group.reserve(totalPeriods);
		int free_time = FREE_TIME;

		std::vector<int> subject_list = m_subjectIndexes;
		for (int j = 0; j < totalPeriods; ++j) {
			int item = getRandomItem(subject_list);

			if (item < 0) {
				group.push_back(free_time);
				--free_time;
			} else {
				group.push_back(item);
			}
		}

		std::shuffle(group.begin(), group.end(), std::mt19937(std::random_device()()));
		timetable.push_back(group);
	}
	return timetable;
}

int TimetableGenerator::fitness(const TimetableGenerator::matrix_t& timetable) {
	size_t height = timetable.size();
	size_t width = timetable[0].size();
	int clashes = 0;
	for (size_t i = 0; i < width; ++i) {
		for (size_t j = 0; j < height; ++j) {
			for (size_t k = 0; k < height; ++k) {
				if (k != j && timetable[j][i] >= 0 && timetable[k][i] >= 0 && timetable[j][i] == timetable[k][i]) {
					++clashes;
				}
			}
		}
	}
	return clashes;
}

TimetableGenerator::matrix_t TimetableGenerator::crossover(const TimetableGenerator::matrix_t& parent1,
														   const TimetableGenerator::matrix_t& parent2) {
	size_t size = parent1.size();
	size_t crossoverPoint = random() % (size - 1) + 1;
	matrix_t result;

	for (int i = 0; i < parent1.size(); ++i) {
		std::vector<int> child(parent1[i].begin(), parent1[i].begin() + (long) (crossoverPoint));

		for (int parent2_child: parent2[i]) {
			if (std::find(child.begin(), child.end(), parent2_child) == child.end()) {
				child.push_back(parent2_child);
			}
		}

		result.push_back(child);
	}
	return result;
}

void TimetableGenerator::mutate(TimetableGenerator::matrix_t& board) {
	size_t mutationPoint_x = random() % board.size();
	size_t mutationPoint_y1 = random() % board[0].size();
	size_t mutationPoint_y2 = random() % board[0].size();

	std::swap(board[mutationPoint_x][mutationPoint_y1], board[mutationPoint_x][mutationPoint_y2]);
}


