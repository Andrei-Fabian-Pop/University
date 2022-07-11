//
// Created by andrew on 12/06/22.
//
#include <QApplication>
#include <QPushButton>

#include <fstream>
#include <iostream>

#include "UserList.h"
#include "userwindow.h"
#include "QnA.h"
#include "Quastion.h"
#include "Answer.h"
#include "searchw.h"

int main(int argc, char** argv) {
    QApplication a(argc, argv);

    std::ifstream f("users.txt");
    if (!f.is_open()) {
        std::cout << "f not open\n";
    }
    UserList userList;
    std::string line;
    while (f >> line) {
        User user(line);
        userList.add(user);
    }
    f.close();

    std::ifstream g("questions.txt");
    if (!g.is_open()) {
        std::cout << "g not open\n";
    }
    std::vector<Question> q;
    std::vector<std::string> out;
    while (g >> line) {
        out.clear();
        size_t start;
        size_t end = 0;
        while ((start = line.find_first_not_of(',', end)) != std::string::npos) {
            end = line.find(',', start);
            out.push_back(line.substr(start, end - start));
        }
        Question aux(std::stoi(out[0]), out[1], out[2]);
        q.push_back(aux);
    }
    g.close();

    std::ifstream h("answeres.txt");
    if (!h.is_open()) {
        std::cout << "h not open\n";
    }

    std::vector<Answer> ans;
    while (h >> line) {
        out.clear();
        size_t start;
        size_t end = 0;
        while ((start = line.find_first_not_of(',', end)) != std::string::npos) {
            end = line.find(',', start);
            out.push_back(line.substr(start, end - start));
        }
        Answer answer(std::stoi(out[0]), std::stoi(out[1]), out[2], out[3], std::stoi(out[4]));
        ans.push_back(answer);
    }
    h.close();

    QnA qnA(q, ans);
    qnA.sorta();

    for (const auto& user : userList.getAll()) {
        auto* newWindow = new UserWindow(user, qnA);
        newWindow->show();
    }

    SearchW w(qnA);
    w.show();

    return QApplication::exec();
}

//1,txt1,me2
//2,txt2,me2
//3,txt3,me1


//1,1,me1,txt1,2
//2,1,me1,txt2,4
//3,2,me2,txt3,6