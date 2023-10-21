#include "SymbolTable.h"

SymbolTable::SymbolTable() : m_size(0), m_capacity(INITIAL_CAPACITY), m_nodes(new Node* [INITIAL_CAPACITY]) {
	for (int i = 0; i < m_capacity; ++i) {
		m_nodes[i] = nullptr;
	}
}

SymbolTable::~SymbolTable() {
	Node* node;
	for (int i = 0; i < m_capacity; ++i) {
		node = m_nodes[i];
		while (node) {
			Node* next = node->next;
			delete node;
			node = next;
		}
	}

	delete[] m_nodes;
}

void SymbolTable::insert(std::string name, std::variant<ATOMIC_TYPES_ALLOWED> item) {
	if ((double)(m_size + 1) / (double)(m_capacity) >= LOAD_FACTOR) {
		this->resize();
	}

	unsigned int index = this->hash(name);
	Node*& nodeRow = m_nodes[index];

	if (nodeRow == nullptr) {
		nodeRow = new Node;
		nodeRow->name = std::move(name);
		nodeRow->var = item;
		nodeRow->next = nullptr;
		++m_size;
		return;
	}

	if (nodeRow->name == name) {
		nodeRow->var = item;
		return;
	}

	while (nodeRow->next) {
		if (nodeRow->name == name) {
			nodeRow->var = item;
			return;
		}
		nodeRow = nodeRow->next;
	}

	nodeRow->next = new Node;
	nodeRow->next->name = name;
	nodeRow->next->var = item;
	nodeRow->next->next = nullptr;
	++m_size;
}

void SymbolTable::remove(const std::string& name) {
	unsigned int index = this->hash(name);
	Node*& prevNode = m_nodes[index];
	Node* currentNode;

	if (prevNode->name == name) {
		delete prevNode;
		prevNode = nullptr;
		--m_size;
		return;
	}

	if (prevNode->next != nullptr) {
		currentNode = prevNode->next;
	} else {
		return;
	}

	while (currentNode) {
		if (currentNode->name == name) {
			prevNode->next = currentNode->next;
			delete currentNode;
			currentNode = nullptr;
			--m_size;
			return;
		}

		prevNode = currentNode;
		currentNode = currentNode->next;
	}
}

bool SymbolTable::contains(const std::string& name) const {
	unsigned int index = this->hash(name);
	Node* nodeRow = m_nodes[index];
	while (nodeRow) {
		if (nodeRow->name == name) {
			return true;
		}

		nodeRow = nodeRow->next;
	}

	return false;
}

unsigned int SymbolTable::size() const {
	return m_size;
}

unsigned int SymbolTable::hash(const std::string& id) const {
	unsigned int result = 0;
	for (char character: id) {
		result += character;
	}

	result %= m_capacity;
	return result;
}

void SymbolTable::resize() {
	auto* newSym = new SymbolTable();
	newSym->m_capacity = m_capacity * 2;

	Node* node;
	for (int i = 0; i < m_capacity; ++i) {
		node = m_nodes[i];
		while (node) {
			Node* next = node->next;
			newSym->insert(node->name, node->var);
			delete node;
			node = next;
		}
	}

	this->m_nodes = newSym->m_nodes;
	this->m_size = newSym->m_size;
	this->m_capacity = newSym->m_capacity;
}


std::variant<ATOMIC_TYPES_ALLOWED>& SymbolTable::get(const std::string& name) const {
	unsigned int index = this->hash(name);
	Node* nodeRow = m_nodes[index];
	while (nodeRow) {
		if (nodeRow->name == name) {
			return nodeRow->var;
		}

		nodeRow = nodeRow->next;
	}
}

std::variant<ATOMIC_TYPES_ALLOWED>& SymbolTable::operator[](const std::string& name) const {
	return this->get(name);
}
