//
// Created by andrew on 26/05/22.
//

#include "Document.h"

#include <utility>

Document::Document(std::string name, std::vector<std::string> keywords, std::string content)
        : name(std::move(name)), keywords(std::move(keywords)), content(std::move(content)) {}

const std::string &Document::getName() const {
    return name;
}

void Document::setName(const std::string &_name) {
    Document::name = _name;
}

const std::vector<std::string> &Document::getKeywords() const {
    return keywords;
}

void Document::setKeywords(const std::vector<std::string> &_keywords) {
    Document::keywords = _keywords;
}

const std::string &Document::getContent() const {
    return content;
}

void Document::setContent(const std::string &_content) {
    Document::content = _content;
}

Document::~Document() = default;
