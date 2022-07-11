//
// Created by andrew on 02.05.2022.
//

#include "UI.h"


Graph UI::readFile(const std::string &file) {
    {
        std::ifstream f(file, std::ios::in);
        if (!f.is_open()) {
            throw std::exception();
        }
        int nrNodes, nrArcs;
        f >> nrNodes >> nrArcs;
        Graph G(nrNodes);
        for (int i = 0; i < nrArcs; ++i) {
            int v1, v2, cost;
            f >> v1 >> v2 >> cost;
            if (!G.isArc(v1, v2)) {
                G.addArc(v1, v2, cost);
            }
        }
        f.close();
        return G;
    }
}

Graph UI::generateGraph(int nrNodes, int nrArcs) {
    Graph G(nrNodes);
    unsigned int v1, v2, cost;
    for (int i = 0; i < nrArcs; ++i) {
        v1 = rand() % nrNodes;
        v2 = rand() % nrNodes;
        cost = rand() % 300;
        if (G.isArc((int) (v1), (int) (v2))) {
            --i;
        } else {
            G.addArc((int) (v1), (int) (v2), (int) (cost));
        }
    }
    return G;
}

Graph UI::getGraph() {
    while (true) {
        std::cout << "How do you want to initialise the graph:\n1 - generate\n2 - read from file\n0 - exit program\n>";
        int cmd;
        std::cin >> cmd;
        if (cmd == 0) {
            std::cout << "Program terminating...\n";
            exit(0);
        } else if (cmd == 1) {
            std::cout << "Please enter number of nodes:";
            int nrNodes, nrArcs;
            std::cin >> nrNodes;
            std::cout << "Please enter number of arcs:";
            std::cin >> nrArcs;
            Graph g = generateGraph(nrNodes, nrArcs);
            return g;
        } else if (cmd == 2) {
            std::cout << "Enter file name:";
            std::string file;
            std::cin >> file;
            Graph g = readFile(file);
            return g;
        } else {
            std::cout << "Invalid option." << std::endl;
        }
    }
}

void UI::printMenu() {
    std::cout << "Graph Operations\n"
                 "1. Get the number of nodes\n"
                 "2. Print the set of nodes\n"
                 "3. Check if there is an arc between 2 nodes\n"
                 "4. Inbound degree of a node\n"
                 "5. Outbound degree of a node\n"
                 "6. Print the inbound arcs of a node\n"
                 "7. Print the outbound arcs of a node\n"
                 "8. Get the cost of an arc\n"
                 "9. Modify the cost of an arc\n"
                 "10. Add arc\n"
                 "11. Remove arc\n"
                 "12. Add node\n"
                 "13. Remove node\n"
                 "14. Save graph to file\n"
                 "15. Print graph\n"
                 "16. Backwards Dijkstra\n"
                 "17. Check if is a DAG\n"
                 "18. Print highest cost of DAG\n"
                 "0. Exit\n";
}

void UI::executeOption(unsigned int cmd, Graph &G) {
    switch (cmd) {
        case 1:
            // "1. Get the number of nodes\n"
            std::cout << G.nrNodes() << '\n';
            break;
        case 2: {
            // "2. Print the set of nodes\n"
            auto p = G.setOfNodes();
            for (auto i = p.first; i != p.second; ++i) {
                std::cout << i->first << ' ';
            }
            std::cout << '\n';
            break;
        }
        case 3: {
            // "3. Check if there is an arc between 2 nodes\n"
            int v1, v2;
            std::cout << "Node 1:";
            v1 = getInteger();
            std::cout << "Node 2:";
            v2 = getInteger();
            if (G.isArc(v1, v2)) {
                std::cout << "There is an arc between " << v1 << " and " << v2 << ".\n";
            } else {
                std::cout << "There is no arc between " << v1 << " and " << v2 << ".\n";
            }
            break;
        }
        case 4: {
            // "4. Inbound degree of a node\n"
            try {
                int v;
                std::cout << "Node: ";
                v = getInteger();
                int deg = G.inDegree(v);
                std::cout << "The inbound degree of the node " << v << " is " << deg << ".\n";
            } catch (std::exception &e) {
                std::cout << "This node does not exist.\n";
            }
            break;
        }
        case 5: {
            // "5. Outbound degree of a node\n"
            try {
                int v;
                std::cout << "Node: ";
                v = getInteger();
                int deg = G.outDegree(v);
                std::cout << "The outbound degree of the node " << v << " is " << deg << ".\n";
            } catch (std::exception &e) {
                std::cout << "This node does not exist.\n";
            }
            break;
        }
        case 6: {
            // "6. Print the inbound arcs of a node\n"
            int v1;
            std::cout << "Node: ";
            v1 = getInteger();
            auto p = G.inboundArc(v1);
            std::cout << "The arcs of the node " << v1 << " are:\n->";
            for (auto i = p.first; i != p.second; ++i) {
                std::cout << *i << ' ';
            }
            std::cout << std::endl;
            break;
        }
        case 7: {
            // "7. Print the outbound arcs of a node\n"
            int v1;
            std::cout << "Node: ";
            v1 = getInteger();
            auto p = G.outboundArc(v1);
            std::cout << "The outbound arcs of the node " << v1 << " are:\n->";
            for (auto i = p.first; i != p.second; ++i) {
                std::cout << *i << ' ';
            }
            std::cout << std::endl;
            break;
        }
        case 8: {
            // "8. Get the cost of an arc\n"
            try {
                int v1, v2;
                std::cout << "Node 1:";
                v1 = getInteger();
                std::cout << "Node 2:";
                v2 = getInteger();
                int cost = G.getCost(v1, v2);
                std::cout << "The cost is: " << cost << '\n';
            } catch (std::exception &e) {
                std::cout << "This arc does not exist.\n";
            }
            break;
        }
        case 9: {
            // "9. Modify the cost of an arc\n"
            try {
                int v1, v2, cost;
                std::cout << "Node 1:";
                v1 = getInteger();
                std::cout << "Node 2:";
                v2 = getInteger();
                std::cout << "Cost: ";
                std::cin >> cost;
                G.changeCost(v1, v2, cost);
                std::cout << "Arc cost changed successfully.\n";
            } catch (std::exception &e) {
                std::cout << "This arc does not exist.\n";
            }
            break;
        }
        case 10: {
            // "10. Add arc\n"
            try {
                int v1, v2, cost;
                std::cout << "Node 1:";
                v1 = getInteger();
                std::cout << "Node 2:";
                v2 = getInteger();
                std::cout << "Cost: ";
                std::cin >> cost;
                G.addArc(v1, v2, cost);
                std::cout << "Arc added successfully." << std::endl;
            } catch (std::exception &e) {
                std::cout << "Arc already exists." << std::endl;
            }
            break;
        }
        case 11: {
            // "11. Remove arc\n"
            try {
                int v1, v2;
                std::cout << "Node 1:";
                v1 = getInteger();
                std::cout << "Node 2:";
                v2 = getInteger();
                G.removeArc(v1, v2);
            } catch (std::exception &e) {
                std::cout << "This arc does not exist.\n";
            }
            break;
        }
        case 12: {
            // "12. Add node\n"
            try {
                int n;
                std::cout << "Node:";
                n = getInteger();
                G.addNode(n);
                std::cout << "Added node: " << n << std::endl;
            } catch (std::exception &e) {
                std::cout << "This node already exists.\n";
            }
            break;
        }
        case 13: {
            // "13. Remove node\n"
            try {
                int v1;
                std::cout << "Node: ";
                v1 = getInteger();
                G.removeNode(v1);
            } catch (std::exception &e) {
                std::cout << "No such node exists.\n";
            }
            break;
        }
        case 14: {
            // "14. Save graph to file\n"
            std::string fileName;
            std::cout << "File name: ";
            std::cin >> fileName;
            std::cout << "The copy of the graph is saved to " << fileName << "...\n";
            std::ofstream graphCopy(fileName);
            graphCopy << G.toString();
            graphCopy.close();
            break;
        }
        case 15: {
            // "15. Print graph\n"
            std::cout << G.toString() << '\n';
            break;
        }
        case 16: {
            // "16. Backwards Dijkstra\n"
            try {
                int st, en;
                std::cout << "Start node: ";
                st = getInteger();
                std::cout << "End node: ";
                en = getInteger();
                std::pair<std::vector<int>, std::vector<int>> dists = G.backwardsDijkstra(st, en);
                if (dists.first[st] == INT32_MAX) {
                    std::cout << "There is no path between " << st << " and " << en << std::endl;
                } else {
                    std::cout << "The minimum cost path between " << st << " and " << en << " is " << dists.first[st]
                              << std::endl;
                    printDijkstraPath(dists.second, st);
                    std::cout << en;
                    std::cout << std::endl << std::endl;
                }
            } catch (std::exception &e) {
                std::cerr << "This node does not exist.\n";
            }
            break;
        }
        case 17: {
            try {
                std::vector<int> topOrder = G.topologicalSort();
                std::cout << "It is a DAG.\n";
                for (int i : topOrder)
                    std::cout << i << " ";
                std::cout << std::endl;
                for (int i: topOrder)
                    std::cout << G.inDegree(i) << " ";
                std::cout << std::endl;
            }
            catch (std::exception& e) {
                std::cout << "There exists a cycle in the graph! It is not a DAG.\n\n";
            }
            break;
        }
        case 18: {
            try {
                std::vector<int> topOrder = G.topologicalSort();
                int v1, v2;
                std::cout << "Choose your vertices:\n" << "Start: ";
                std::cin >> v1;
                std::cout << "End: ";
                std::cin >> v2;
                std::vector<int> costs = G.highestCostPathWithTopologicalSort(topOrder, v1);
                std::cout << "Highest cost path from " << v1 << " to " << v2 << " is: ";
                std::cout << costs[v2] << "\n\n";
            } catch (std::exception &e) {
                std::cout << "There exists a cycle in the graph! It is not a DAG.\n\n";
            }
            break;
        }
        case 0:
            throw std::exception();
        default:
            std::cout << "Invalid command\n";
            break;
    }
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

void UI::printDijkstraPath(const std::vector<int> &paths, int j) {
    if (paths[j] == -1)
        return;
    std::cout << j << "->";
    printDijkstraPath(paths, paths[j]);
}

#pragma clang diagnostic pop

int UI::getInteger() {
    int user_input;
    bool is_correct;
    std::cin.exceptions(std::istream::failbit);
    do {
        try {
            std::cout << "> ";
            std::cin >> user_input;
            std::cin.clear();
            is_correct = true;
        } catch (std::ios_base::failure &failure) {
            is_correct = false;
            std::cout << "This input is invalid, please enter an integer" << std::endl;
            std::cin.clear();
            std::cin.get();
        }
    } while (!is_correct);

    return user_input;
}

void UI::start() {
    Graph G = Graph(0);
    try {
        G = getGraph();
    } catch (std::exception &e) {
        std::cout << "Invalid data. Terminating program.\n";
        exit(-1);
    }
    while (true) {
        try {
            printMenu();
            unsigned int command = getInteger();
            executeOption(command, G);
        } catch (std::exception &e) {
            exit(0);
        }
    }
}
