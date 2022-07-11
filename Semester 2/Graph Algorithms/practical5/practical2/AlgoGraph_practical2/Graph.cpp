//
// Created by andre on 03/04/2022.
//

#include "Graph.h"
#include <exception>
#include <algorithm>
#include <iostream>

Graph::Graph(int nrVertices) {
    for (int i = 0; i < nrVertices; ++i) {
        arcsMap[i] = std::vector<int>();
    }
}

int Graph::nrNodes() {
    return (int)(arcsMap.size());
}

int Graph::nrArcs() {
    return (int)(costMap.size());
}

std::pair<std::map<int, std::vector<int>>::iterator , std::map<int, std::vector<int>>::iterator> Graph::setOfNodes() {
    return std::make_pair(arcsMap.begin(), arcsMap.end());
}

bool Graph::isNode(int v) {
    return arcsMap.find(v) != arcsMap.end();
}

bool Graph::isArc(int v1, int v2) {
    return std::find(arcsMap[v1].begin(), arcsMap[v1].end(), v2) != arcsMap[v1].end();
}

void Graph::addArc(int v1, int v2, int cost) {
    if (!isNode(v1) || !isNode(v2) || isArc(v1, v2)) {
//        throw std::exception();
    } else {
        costMap[std::make_pair(v1, v2)] = cost;
        arcsMap[v1].push_back(v2);
        if (v1 != v2) {
            arcsMap[v2].push_back(v1);
        }
    }
}

int Graph::arcDegree(int x) {
    if (arcsMap.find(x) == arcsMap.end()) {
        throw std::exception();
    }
    return (int)(arcsMap[x].size());
}

std::pair<std::vector<int>::iterator, std::vector<int>::iterator> Graph::arcList(int x) {
    return std::make_pair(arcsMap[x].begin(), arcsMap[x].end());
}

void Graph::changeCost(int x, int y, int val) {
    if (isArc(x,y)) {
        costMap[std::make_pair(x, y)] = val;
    } else if (isArc(y, x)) {
        costMap[std::make_pair(y, x)] = val;
    } else {
        throw std::exception();
    }
}

int Graph::getCost(int x, int y) {
    if (isArc(x,y)) {
        return costMap[std::make_pair(x, y)];
    } else if (isArc(y, x)) {
        return costMap[std::make_pair(y, x)];
    } else {
        throw std::exception();
    }
}

void Graph::removeArc(int x, int y) {
    if (!isArc(x, y)) {
        throw std::exception();
    }
    for (auto &elem : costMap) {
        if (y == elem.first.second && x == elem.first.first) {
            costMap.erase(elem.first);
            break;
        }
    }
    arcsMap[y].erase(std::find(arcsMap[y].begin(), arcsMap[y].end(), x));
    arcsMap[x].erase(std::find(arcsMap[x].begin(), arcsMap[x].end(), y));
}

void Graph::addNode(int val) {
    if (isNode(val)) {
        throw std::exception();
    }
    arcsMap[val] = std::vector<int>();
}

void Graph::removeNode(int val) {
    if (arcsMap.find(val) == arcsMap.end()) {
        throw std::exception();
    }
    arcsMap.erase(arcsMap.find(val));
    unsigned int len = costMap.size();
    std::vector<std::pair<int, int>> array;
    for (auto& el : costMap) {
        array.push_back(el.first);
    }

    std::map<std::pair<int, int>, int> newCostMap;
    for (int i = 0; i < len; ++i) {
        if (array[i].second == val || array[i].first == val) {
            costMap.erase(costMap.find(array[i]));
            array.erase(std::find(array.begin(), array.end(), array[i]));
            --len;
            continue;
        }
        int x = array[i].first;
        int y = array[i].second;
        if (x > val) --x;
        if (y > val) --y;
        newCostMap[std::make_pair(x, y)] = costMap[array[i]];
    }
    costMap = newCostMap;

    std::map<int, std::vector<int>> newArcsMap;
    for (auto el : arcsMap) {
        auto c = std::find(el.second.begin(), el.second.end(), val);
        if (c != el.second.end()) {
            el.second.erase(c);
        }
    }
    for (int i = 0; i < arcsMap.size(); ++i) {
        int x = i;
        if (x > val) --x;
        newArcsMap[x] = arcsMap[i];
        for (int j = 0; j < arcsMap[i].size(); ++j) {
            if (arcsMap[i][j] > val) {
                newArcsMap[x][j] = arcsMap[i][j] - 1;
            }
        }
    }
    arcsMap = newArcsMap;
}

std::string Graph::toString() {
    std::string str;
    str += std::to_string(nrNodes()) + " " + std::to_string(nrArcs()) + "\n";
    for (auto i: costMap) {
        str += std::to_string(i.first.first) + " " + std::to_string(i.first.second) + " " + std::to_string(i.second) + "\n";
    }
    return str;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
void Graph::DFS(int currentNode, bool *visited, std::list<int>& component) {
    visited[currentNode] = true;
    component.push_back(currentNode);

    for (auto it = this->arcsMap[currentNode].begin(); it != this->arcsMap[currentNode].end(); ++it) {
        if (!visited[*it]) {
            DFS(*it, visited, component);
        }
    }
}
#pragma clang diagnostic pop

std::list<std::list<int>> Graph::connectedComponents() {
    int nr_nodes = this->nrNodes();

    bool* visited = new bool [nr_nodes];
    for (int i = 0; i < nr_nodes; ++i) visited[i] = false;

    std::list<std::list<int>> compList;

    for (int i = 0; i < nr_nodes; ++i) {
        if (!visited[i]) {
            compList.emplace_back();
            DFS(i, visited, compList.back());
        }
    }

    delete[] visited;

    std::vector<Graph> graphList;

    for (const auto& graph: compList) {
        Graph graph1(0);
        for (auto vertex: graph) {
            graph1.addNode(vertex);
        }
        for (auto vertex: graph) {
            for (auto connection = this->arcList(vertex).first; connection != this->arcList(vertex).second; ++connection) {
                try {
                    graph1.addArc(vertex, *connection, getCost(vertex, *connection));
                } catch (std::exception& e) {
                    graph1.addArc(*connection, vertex, getCost(*connection, vertex));
                }
            }
        }
        graphList.push_back(graph1);
    }

    // print
    for (auto graph: graphList) {
        for (auto node = graph.setOfNodes().first; node != graph.setOfNodes().second; ++node) {
            std::cout << node->first << " -> [";
            for (auto con: node->second) {
                std::cout << con << " ";
            }
            std::cout << "]\n";
        }
        std::cout << std::endl;
    }

    return compList;
}

