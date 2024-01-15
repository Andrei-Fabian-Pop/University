// 6. Generate a school timetable through genetic algorithms.
#include "timetable_generator.h"
#include "timetable_generator_threadded.h"
#include "timetable_generator_distributed.h"
#include <mpi/mpi.h>

int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);

	for (int i = 0; i < 100; ++i) {
		auto timetable_generator = TimetableGeneratorDistributed();
	}

	auto timetable_generator = TimetableGeneratorDistributed();
	timetable_generator.printTimetables();

	MPI_Finalize();

	return 0;
}

