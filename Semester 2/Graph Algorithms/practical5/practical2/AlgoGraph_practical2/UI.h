//
// Created by andre on 03/04/2022.
//

#ifndef PRACTICAL2_UI_H
#define PRACTICAL2_UI_H

#include "Graph.h"
#include <iostream>
#include <fstream>
#include <exception>

class UI {
private:
    static Graph getGraph();
    static void printMenu();
    static void executeOption(unsigned int cmd, Graph& G);
    static int getInteger();
public:
    static Graph readFile(const std::string& file);
    static Graph generateGraph(int nrNodes, int nrArcs);
    static void start();
};


#endif //PRACTICAL2_UI_H
