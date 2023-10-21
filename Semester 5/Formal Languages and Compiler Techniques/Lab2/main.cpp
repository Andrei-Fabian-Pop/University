#include <iostream>
#include <iomanip>
#include "SymbolTable.h"

// https://github.com/Andrei-Fabian-Pop/University/pull/3

int main() {
	auto *s = new SymbolTable();

	// inserts
	s->insert("a", 77);
	s->insert("b",'a');
	s->insert("c",false);
	s->insert("d",4.8);

	// test good insert
	std::cout << s->size() << "\n";
	std::cout << s->contains("a") << " " << s->contains("b") << " " << s->contains("c") << " " << s->contains("d")<< "\n";

	// test casting
	try {
		std::cout << "Double: " << std::get<double>(s->get("d")) << "\n";
	} catch (std::bad_variant_access& err) {
		std::cerr << "The variable d was not correctly casted.";
	}

	// test type-check
	std::cout << SymbolTable::typeCheck<int>(s->get("a")) << " "; // 1
	std::cout << SymbolTable::typeCheck<char>(s->get("a")) << " "; // 0
	std::cout << SymbolTable::typeCheck<bool>(s->get("a")) << " "; // 0

	std::cout << SymbolTable::typeCheck<char>(s->get("b")) << " "; // 1
	std::cout << SymbolTable::typeCheck<bool>(s->get("c")) << " "; // 1
	std::cout << SymbolTable::typeCheck<double>(s->get("d")) << "\n"; // 1

	// test remove
	s->remove("a");
	s->remove("b");
	s->remove("c");
	s->remove("d");

	// test size
	std::cout << s->size()<< "\n";

	delete s;
	return 0;
}
