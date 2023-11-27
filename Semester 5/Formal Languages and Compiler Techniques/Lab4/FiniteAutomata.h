#ifndef LAB4_FINITEAUTOMATA_H
#define LAB4_FINITEAUTOMATA_H

#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <set>

// 1.a. recursive descendent

#define TRANSITION_MAP_T std::map<std::pair<std::string, std::string>, std::vector<char>>

class FiniteAutomata {
public:
	explicit FiniteAutomata(std::string fileName);

	std::vector<std::string> getAutomatas();
	std::set<char> getAlphabet(const std::string& automata);
	std::set<std::string> getStates(const std::string& automata);
	std::string getInitialState(const std::string& automata);
	std::string getFinalState(const std::string& automata);
	TRANSITION_MAP_T getTransitions(const std::string& automata);
	std::string verifyLexeme(const std::string&);

private:
	struct Automata {
		std::set<std::string> states;
		std::set<char> alphabet;
		std::string initial_state;
		std::string final_state;
		TRANSITION_MAP_T transitions;
	};

	std::string m_fileName;
	std::map<std::string, Automata*> m_automatas;

	void init();
	static std::vector<std::string> split(const std::string &s, char delim);
	bool verifyAutomata(const std::string& current_state,
						const std::string& final_state,
						const TRANSITION_MAP_T& transitions,
						std::string lexeme, int index = 0);
};


#endif //LAB4_FINITEAUTOMATA_H
