#include <iostream>
#include <fstream>

#include "Scanner.h"

// https://github.com/Andrei-Fabian-Pop/University/pull/3

int main(int argc, char **argv) {
	if (argc < 2) {
		std::cerr << "No file provided\n";
		return -ENODATA;
	}

	auto scanner = new Scanner();

	std::ifstream file;
	file.open(argv[1], std::fstream::in);
	if (!file.is_open()) {
		std::cerr << "Failed to open the file: " << argv[1] << std::endl;
		return -ENODATA;
	}
	std::string programText;
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	programText = buffer.str();

	scanner->setProgramText(programText);

	return 0;
}
