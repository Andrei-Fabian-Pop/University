#include <iostream>

#include "FiniteAutomata.h"
#include "Scanner.h"

void startScanner() {
	auto scanner = new Scanner();

	std::ifstream file;
	file.open("../program.in", std::fstream::in);
	if (!file.is_open()) {
		std::cerr << "Failed to open the file: ../program.in" << std::endl;
		return;
	}
	std::string programText;
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	programText = buffer.str();

	scanner->setProgramText(programText);
}

void testFiniteAutomata() {
	FiniteAutomata finiteAutomata("../fa.in");

	std::string option = "m";
	std::string automata;
	while (option != "x") {
		if (option == "m") {
			std::cout << "x: exit\nm: menu\n0: Select Automata\n1: States\n2: Alphabet\n3: Transitions\n4: Initial State\n5: Final State\n6: Check Lexeme\n\n";
		}
		if (option == "0") {
			std::cout << "Select automata:\n";
			int i = 0;
			for (const auto& item: finiteAutomata.getAutomatas()) {
				std::cout << i++ << ": " << item << "\n";
			}

			std::string choice;
			std::cin >> choice;
			automata = finiteAutomata.getAutomatas()[stoi(choice)];
		}
		if (option == "1") {
			if (!automata.empty()) {
				auto states = finiteAutomata.getStates(automata);
				for (const auto& item: states) {
					std::cout << item << "\n";
				}
			}
		}
		if (option == "2") {
			if (!automata.empty()) {
				auto alphabet = finiteAutomata.getAlphabet(automata);
				for (const auto& item: alphabet) {
					std::cout << item << "\n";
				}
			}
		}
		if (option == "3") {
			if (!automata.empty()) {
				auto transitions = finiteAutomata.getTransitions(automata);
				for (const auto& transition: transitions) {
					std::cout << "initial state: " << transition.first.first << "\n";
					for (auto item: transition.second) {
						std::cout << item << ",";
					}
					std::cout << "\n" << "final state: " << transition.first.second << "\n";
				}
			}
		}
		if (option == "4") {
			if (!automata.empty()) {
				auto states = finiteAutomata.getInitialState(automata);
				std::cout << "Initial state: " << states << "\n";
			}
		}
		if (option == "5") {
			if (!automata.empty()) {
				auto states = finiteAutomata.getFinalState(automata);
				std::cout << "Final state: " << states << "\n";
			}
		}
		if (option == "6") {
			std::string lexeme;
			std::cout << "Enter lexeme: ";
			std::cin >> lexeme;
			std::cout << finiteAutomata.verifyLexeme(lexeme) << "\n";
		}

		std::cout << "Enter option:\n";
		std::cin >> option;
	}

//	auto automatas = finiteAutomata.getAutomatas();
//	auto alphabet = finiteAutomata.getAlphabet(automatas[0]);
//	auto states = finiteAutomata.getStates(automatas[0]);
//	auto initial_state = finiteAutomata.getInitialState(automatas[0]);
//	auto final_state = finiteAutomata.getFinalState(automatas[0]);
//	auto transitions = finiteAutomata.getTransitions(automatas[0]);
//
//	std::cout << finiteAutomata.verifyLexeme("ab") << "\n";
//	std::cout << finiteAutomata.verifyLexeme("12x") << "\n";
//	std::cout << finiteAutomata.verifyLexeme("x12") << "\n";
//	std::cout << finiteAutomata.verifyLexeme("12") << "\n";
//	std::cout << finiteAutomata.verifyLexeme("-12") << "\n";
//	std::cout << finiteAutomata.verifyLexeme("-0") << "\n";
}

int main() {
	testFiniteAutomata();

	return 0;
}
