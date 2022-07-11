#include <iostream>
#include "graph.h"
#include <fstream>
#include <exception>
#include <random>

Graph readFile(const std::string& file) {
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
        G.addArc(v1, v2, cost);
    }
    f.close();
    return G;
}

Graph generateGraph(int nrNodes, int nrArcs) {
    Graph G(nrNodes);
    unsigned int v1, v2, cost;
    for (int i = 0; i < nrArcs; ++i) {
        v1 = rand() % nrNodes;
        v2 = rand() % nrNodes;
        cost = rand() % 300;
        if (G.isArc((int) (v1), (int) (v2))) {
            i--;
        }else {
            G.addArc((int) (v1), (int) (v2), (int) (cost));
        }
    }
    return G;
}

Graph getGraph() {
    std::cout << "How do you want to initialise the graph:\n1 - generate\n2 - read from file\n>";
    int cmd;
    std::cin >> cmd;
    if (cmd == 1) {
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
        std::cout << "Invalid option.";
        throw std::exception();
    }
}

void printMenu(Graph& G) {
    std::cout << "Graph Operations\n"
                 "1. Get the number of nodes\n"
                 "2. Print the set of nodes\n"
                 "3. Check if there is an arc between 2 nodes\n"
                 "4. Inbound degree of a node\n"
                 "5. Outbound degree of a node\n"
                 "6. The outbound arcs of a node\n"
                 "7. The inbound arcs of a node\n"
                 "8. Get the cost of an arc\n"
                 "9. Modify the cost of an arc\n"
                 "10. Add arc\n"
                 "11. Remove arc\n"
                 "12. Add node\n"
                 "13. Remove node\n"
                 "14. Save graph to file\n"
                 "15. Print graph\n"
                 "0. Exit\n";
    int cmd;
    std::cout << "Command: ";
    std::cin >> cmd;
    switch (cmd) {
        case 1:
            std::cout << G.nrNodes() << '\n';
            break;
        case 2: {
            auto p = G.setOfNodes();
            for (auto i = p.first; i != p.second; ++i) {
                std::cout << i->first << ' ';
            }
            std::cout << '\n';
            break;
        }
        case 3: {
            int v1, v2;
            std::cout << "Nodes: ";
            std::cin >> v1 >> v2;
            std::cout << G.isArc(v1, v2) << '\n';
            break;
        }
        case 4: {
            int v1;
            std::cout << "Node: ";
            std::cin >> v1;
            std::cout << G.inDegree(v1) << '\n';
            break;
        }
        case 5: {
            int v1;
            std::cout << "Node: ";
            std::cin >> v1;
            std::cout << G.outDegree(v1) << '\n';
            break;
        }
        case 6: {
            int v1;
            std::cout << "Node: ";
            std::cin >> v1;
            auto p = G.outboundArc(v1);
            for (auto i = p.first; i != p.second; ++i) {
                std::cout << *i << '\n';
            }
            break;
        }
        case 7: {
            int v1;
            std::cout << "Node: ";
            std::cin >> v1;
            auto p = G.inboundArc(v1);
            for (auto i = p.first; i != p.second; ++i) {
                std::cout << *i << '\n';
            }
            break;
        }
        case 8: {
            try {
                int v1, v2;
                std::cout << "Arc: ";
                std::cin >> v1 >> v2;
                std::cout << G.getCost(v1, v2) << '\n';
            } catch (std::exception& e) {
                std::cout << "This arc does not exist.\n";
            }
            break;
        }
        case 9: {
            try {
                int v1, v2, cost;
                std::cout << "Arc: ";
                std::cin >> v1 >> v2;
                std::cout << "Cost: ";
                std::cin >> cost;
                G.changeCost(v1, v2, cost);
                std::cout << "Arc added successfully.\n";
            } catch (std::exception& e) {
                std::cout << "This arc does not exist.\n";
            }
            break;
        }
        case 10: {
            try {
                int v1, v2, cost;
                std::cout << "Arc: ";
                std::cin >> v1 >> v2;
                std::cout << "Cost: ";
                std::cin >> cost;
                G.addArc(v1, v2, cost);
                std::cout << "Arc added successfully." << std::endl;
            } catch (std::exception& e) {
                std::cout << "Arc is already added." << std::endl;
            }
            break;
        }
        case 11: {
            try {
                int v1, v2;
                std::cout << "Arc: ";
                std::cin >> v1 >> v2;
                G.removeArc(v1, v2);
            } catch (std::exception& e) {
                std::cout << "This arc does not exist.\n";
            }
            break;
        }
        case 12: {
            try {
                G.addNode(G.nrNodes());
                std::cout << "Added node: " << G.nrNodes() - 1 << std::endl;
            } catch (std::exception& e) {
                std::cout << "This node already exists.\n";
            }
            break;
        }
        case 13: {
            int v1;
            std::cout << "Node: ";
            std::cin >> v1;
            G.removeNode(v1);
            break;
        }
        case 14: {
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
            std::cout << G.toString() << '\n';
            break;
        }
        case 0:
            throw std::exception();
        default:
            std::cout << "Invalid command\n";
            break;
    }
}

int main() {
    Graph G = Graph(0);
    try {
        G = getGraph();
    } catch (std::exception& e) {
        std::cout << "Invalid data. Terminating program.\n";
        return -1;
    }
    while (true) {
        try {
            printMenu(G);
        } catch (std::exception& e) {
            return 0;
        }
    }
}
