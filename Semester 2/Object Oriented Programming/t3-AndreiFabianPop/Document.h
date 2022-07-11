//
// Created by andrew on 26/05/22.
//

#ifndef T3_ANDREIFABIANPOP_DOCUMENT_H
#define T3_ANDREIFABIANPOP_DOCUMENT_H

#include <string>
#include <vector>

class Document {
private:
    std::string name;
    std::vector<std::string> keywords;
    std::string content;
public:
    Document(std::string name, std::vector<std::string> keywords, std::string content);
    ~Document();

    [[nodiscard]] const std::string &getName() const;

    void setName(const std::string &_name);

    [[nodiscard]] const std::vector<std::string> &getKeywords() const;

    void setKeywords(const std::vector<std::string> &_keywords);

    [[nodiscard]] const std::string &getContent() const;

    void setContent(const std::string &_content);
};


#endif //T3_ANDREIFABIANPOP_DOCUMENT_H
