#ifndef LAB2_SCANNER_H
#define LAB2_SCANNER_H

#include <string>
#include <vector>
#include <regex>
#include <optional>
#include "SymbolTable.h"

#define IDENTIFIER_REGEX R"(^[a-zA-Z_]\w*$)"
#define CONSTANTS_REGEX R"(^((\d|[1-9]\d*)|(\"[^\"]*\"))$)"

class Scanner {
public:
	explicit Scanner(std::string program_text);
	Scanner();
	~Scanner();

	void setProgramText(std::string program_text);

private:
	void parse();
	static std::vector<std::string> getLexemes(const std::string& row);
	static std::vector<std::string> initLexemes(const std::string& file_content);

	SymbolTable *m_symTable;
	std::string m_text;
};


#endif //LAB2_SCANNER_H
