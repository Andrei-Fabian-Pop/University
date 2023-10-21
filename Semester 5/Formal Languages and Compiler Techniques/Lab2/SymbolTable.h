#ifndef LAB2_SYMBOLTABLE_H
#define LAB2_SYMBOLTABLE_H

#include <string>
#include <atomic>
#include <variant>
#include <iostream>

#define ATOMIC_TYPES_ALLOWED int, char, double, bool
#define INITIAL_CAPACITY 256
#define LOAD_FACTOR 0.7

template<class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };

template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

struct Node {
	std::string name; // identifier
	std::variant<ATOMIC_TYPES_ALLOWED> var; // value
	Node* next; // used for conflict resolution
};

class SymbolTable {
public:
	explicit SymbolTable();

	~SymbolTable();

	/**
	 * @brief Inserts a key-value pair in the HashMap. If the key already exists, its value will be overridden. If that
	 * is a problem, call the contains() function first to check if the key exists.
	 * @param name The identifier for the key-value pair.
	 * @param item A std::variant that contains all allowed types. These can be found under the ATOMIC_TYPES_ALLOWED macro.
	 * */
	void insert(std::string name, std::variant<ATOMIC_TYPES_ALLOWED> item);

	/**
	 * @brief Removes a key-value pair in the HashMap, if the value does not exist, nothing is done.
	 * @param name The identifier of the pair to be deleted.
	 * */
	void remove(const std::string& name);

	/**
	 * @brief Check weather the key provided is contained in the HashMap.
	 * @param name The key to search for.
	 * @return True if the key is in the HashMap, false otherwise.
	 * */
	[[nodiscard]] bool contains(const std::string& name) const;

	/**
	 * @brief Returns the number of elements in the HashMap.
	 * @return unsigned int
	 * */
	[[nodiscard]] unsigned int size() const;

	/**
	 * @brief Returns the std::variant with the key provided as parameter. It is the user's responsibility to check that
	 * the key already exists before calling this
	 * @param name They key for the return value.
	 * @return std::variant<ATOMIC_TYPES_ALLOWED>&
	 * */
	[[nodiscard]] std::variant<ATOMIC_TYPES_ALLOWED>& get(const std::string& name) const;

	/**
	 * @brief Returns the std::variant with the key provided as parameter. It is the user's responsibility to check that
	 * the key already exists before calling this
	 * @param name They key for the return value.
	 * @return std::variant<ATOMIC_TYPES_ALLOWED>&
	 * */
	std::variant<ATOMIC_TYPES_ALLOWED>& operator[](const std::string& name) const;

	/**
	 * @brief Checks weather the templated type matches the type in the std::variant.
	 * */
	template<typename T>
	static bool typeCheck(std::variant<ATOMIC_TYPES_ALLOWED> variant) {
		return std::visit(overloaded{
				[](T arg) { return true; },
				[](auto arg) { return false; }
		}, variant);
	}

private:
	/**
	 * @brief Computes the hash of the provided id by adding all the letter codes. After that a modulo capacity is
	 * performed on the result and that is the final hash code.
	 * @param id The string with the identifier.
	 * */
	[[nodiscard]] unsigned int hash(const std::string& id) const;

	/**
	 * @brief Doubles the capacity of the HashMap
	 * */
	void resize();

	unsigned int m_size;
	unsigned int m_capacity;
	Node** m_nodes;
};

#endif //LAB2_SYMBOLTABLE_H
