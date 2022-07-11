//
// Created by andrew on 02.05.2022.
//

#ifndef ALGOGRAPH_PRACTICAL3_UI_H
#define ALGOGRAPH_PRACTICAL3_UI_H

#include <string>
#include <fstream>
#include <iostream>
#include <list>
#include <climits>

#include "Graph.h"

class UI {
private:
    static Graph getGraph();

    static void printMenu();

    static void executeOption(unsigned int cmd, Graph &G);

    static int getInteger();

    static void printDijkstraPath(const std::vector<int>& paths, int j);

public:
    static Graph readFile(const std::string &file);

    static Graph generateGraph(int nrNodes, int nrArcs);

    static void start();

};


#endif //ALGOGRAPH_PRACTICAL3_UI_H
