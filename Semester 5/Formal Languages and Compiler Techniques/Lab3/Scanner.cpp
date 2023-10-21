#include "Scanner.h"

#include <utility>
#include <stack>
#include <unordered_set>
#include <fstream>


Scanner::Scanner(std::string program_text) : m_text(std::move(program_text)), m_symTable(new SymbolTable()) {
	parse();
}

Scanner::Scanner() : m_symTable(new SymbolTable()) {
//	Scanner::getLexemes("int i;");
//	Scanner::getLexemes("if (a < b) {");
//	Scanner::getLexemes("x = a == b;");
//	Scanner::getLexemes("string >= \'some random string\';");
}

Scanner::~Scanner() {
	delete m_symTable;
}

void Scanner::setProgramText(std::string programText) {
	m_text = std::move(programText);
	parse();
}

void Scanner::parse() {
	int id = 0;
	std::vector<std::string> lexemes = Scanner::initLexemes(m_text);
	std::stack<std::string> parenthesis_stack;
	const std::unordered_set<std::string> reserved_tokens =
			{
					"int", "char", "bool", "double", "if", "else", "print", "read", "return",
					"while", ",", ";", "(", ")", "[", "]", "{", "}", " ", "+", "-",
					"*", "/", "%", "=", "<", ">", "==", ">=", "<=", "&&", "||"
			};
	std::regex identifier_regex(IDENTIFIER_REGEX);
	std::regex constants_regex(CONSTANTS_REGEX);
	std::ofstream pif, sym;
	pif.open("../pif.out");
	sym.open("../sym.out");

	for (const std::string& lex: lexemes) {
		if (reserved_tokens.find(lex) != reserved_tokens.end()) {
			if (!m_symTable->contains(lex)) {
				pif << lex << " " << -1 << "\n";
			}
		} else if (std::regex_match(lex, identifier_regex)) {
			// add to id symtable
			if (!m_symTable->contains(lex)) {
				sym << lex << " " << id << " \n";
				pif << lex << " " << id++ << "\n";
			} else {
				pif << lex << " " << std::get<int>(m_symTable->get(lex)) << "\n";
			}
			m_symTable->insert(lex, id);
		} else if (std::regex_match(lex, constants_regex)) {
			// add to constants symtable
			if (!m_symTable->contains(lex)) {
				sym << lex << " " << id << "\n";
			}
			m_symTable->insert(lex, id);
			pif << lex << " " << id++ << "\n";
		} else {
			// TODO: show the row:line where the error is at
			throw std::runtime_error("Lexically Incorrect\n");
		}
	}

	pif.close();
	sym.close();
	std::cout << "Lexically Correct\n";
}

std::vector<std::string> Scanner::getLexemes(const std::string& row) {
	std::vector<std::string> lexemes;
	const std::unordered_set<char> delimiters = {',', ';', '(', ')', '[', ']', '{', '}', ' ', '+', '-', '*', '/', '%'};
	const std::unordered_set<char> soft_delimiter = {'>', '<', '=', '|', '&'};
	bool in_string = false;
	std::string current_text;

	for (int i = 0; i < row.size(); ++i) {
		if (row[i] == '\'') {
			if (!current_text.empty()) {
				if (in_string) {
					current_text += "\'";
				}
				lexemes.push_back(current_text);
				current_text = "";
			}
			if (!in_string) {
				current_text += "\'";
			}
			in_string = 1 - in_string;
			continue;
		}

		if (in_string) {
			current_text += row[i];
			continue;
		}

		if (delimiters.find(row[i]) != delimiters.end()) {
			if (!current_text.empty()) {
				lexemes.push_back(current_text);
				current_text = "";
			}

			if (row[i] == ' ') {
				continue;
			}
			std::string delimiter;
			delimiter += row[i];
			lexemes.push_back(delimiter);
		} else if (soft_delimiter.find(row[i]) != soft_delimiter.end()) {
			if (row[i] == '=') {
				current_text = current_text;
			}
			if (!current_text.empty()) {
				lexemes.push_back(current_text);
				current_text = "";
			}

			std::string text;
			if (soft_delimiter.find(row[i + 1]) != soft_delimiter.end()) {
				text += row[i];
				text += row[i + 1];
				++i;
			} else {
				text = row[i];
			}
			lexemes.push_back(text);
		} else {
			current_text += row[i];
		}
	}

	if (!current_text.empty()) {
		lexemes.push_back(current_text);
	}

	return lexemes;
}

std::vector<std::string> Scanner::initLexemes(const std::string& file_content) {
	std::istringstream iss(file_content);
	std::string line;
	std::vector<std::string> lexemes;

	while (std::getline(iss, line)) {
		// Call getLexemes for each row (line)
		std::vector<std::string> line_lexemes = Scanner::getLexemes(line);
		for (const std::string& lex: line_lexemes) {
			lexemes.push_back(lex);
		}
	}

	return lexemes;
}
