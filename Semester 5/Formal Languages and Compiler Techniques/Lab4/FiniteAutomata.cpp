#include "FiniteAutomata.h"

#include <utility>
#include <iostream>
#include <sstream>
#include <algorithm>

FiniteAutomata::FiniteAutomata(std::string fileName) : m_fileName(std::move(fileName)) {
	init();
}

void FiniteAutomata::init() {
	std::ifstream file;
	file.open(m_fileName);

	if (!file.is_open()) {
		std::cerr << "Error opening file: " << m_fileName << std::endl;
		return;
	}

	std::string line, current_automata;
	int index = 0;
	while (std::getline(file, line)) {
		if (index == 0) { // automata name
			current_automata = line;
			m_automatas.insert({current_automata, new Automata});
		} else if (index == 1) { // states
			std::vector<std::string> states = FiniteAutomata::split(line, ',');
			for (const auto& state: states) {
				m_automatas[current_automata]->states.insert(state);
			}
		} else if (index == 2) { // alphabet
			std::vector<std::string> alphabet = FiniteAutomata::split(line, ',');
			for (auto character: alphabet) {
				if (character.size() != 1) {
					std::string error =
							"Error: character \"" + character + "\" is not just one character, it is a string\n";
					throw std::runtime_error(error);
				}
				m_automatas[current_automata]->alphabet.insert(character[0]);
			}
		} else if (index == 3) { // initial state
			m_automatas[current_automata]->initial_state = line;
		} else if (index == 4) { // final state
			m_automatas[current_automata]->final_state = line;
		} else if (index > 4) { // transitions
			std::vector<std::string> transition = FiniteAutomata::split(line, ',');
			if (transition.size() < 3) {
				index = 0;
				current_automata = line;
				m_automatas.insert({current_automata, new Automata});
			} else {
				std::string start_state = transition[0];
				std::string end_state = transition[transition.size() - 1];

				transition.erase(transition.begin());
				transition.pop_back();
				std::vector<char> casted_transition;
				for (auto t: transition) {
					if (t.size() > 1) {
						throw std::runtime_error("yak");
					}
					casted_transition.push_back(t[0]);
				}

				m_automatas[current_automata]->transitions.insert({{start_state, end_state}, casted_transition});
			}
		}

		++index;
	}

	file.close();
}

std::vector<std::string> FiniteAutomata::split(const std::string& s, char delim) {
	std::vector<std::string> result;
	std::stringstream ss(s);
	std::string item;

	while (getline(ss, item, delim)) {
		result.push_back(item);
	}

	return result;
}

std::vector<std::string> FiniteAutomata::getAutomatas() {
	std::vector<std::string> automatas;
	for (const auto& key: m_automatas) {
		automatas.push_back(key.first);
	}

	return automatas;
}

std::set<char> FiniteAutomata::getAlphabet(const std::string& automata) {
	return m_automatas[automata]->alphabet;
}

std::set<std::string> FiniteAutomata::getStates(const std::string& automata) {
	return m_automatas[automata]->states;
}

std::string FiniteAutomata::getInitialState(const std::string& automata) {
	return m_automatas[automata]->initial_state;
}

std::string FiniteAutomata::getFinalState(const std::string& automata) {
	return m_automatas[automata]->final_state;
}

TRANSITION_MAP_T FiniteAutomata::getTransitions(const std::string& automata) {
	return m_automatas[automata]->transitions;
}

std::string FiniteAutomata::verifyLexeme(const std::string& lexeme) {
	for (const auto& automata: m_automatas) {
		bool check = verifyAutomata(automata.second->initial_state,
									automata.second->final_state,
									automata.second->transitions,
									lexeme);

		if (check) {
			return automata.first;
		}
	}

	return "NO MATCH";
}

bool FiniteAutomata::verifyAutomata(const std::string& current_state,
									const std::string& final_state,
									const TRANSITION_MAP_T& transitions,
									std::string lexeme, int index) {
	if (current_state == final_state && lexeme.size() == index) {
		return true;
	}
	if (current_state != final_state && lexeme.size() == index) {
		return false;
	}

	bool transitioned = false;
	for (const auto& transition: transitions) {
		auto transition_list = transition.second;
		bool contains = std::find(transition_list.begin(), transition_list.end(), lexeme[index]) != transition_list.end();
		if (transition.first.first == current_state && contains) {
			transitioned = transitioned || verifyAutomata(transition.first.second, final_state, transitions, lexeme, index + 1);
		}
		if (transitioned) {
			return true;
		}
	}
	if (!transitioned) {
		return false;
	}
}
