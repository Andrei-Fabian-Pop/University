#include "graph.h"
#include <exception>
#include <iostream>

Graph::Graph(int nrVertices) {
    for (int i = 0; i < nrVertices; ++i) {
        inboundMap[i] = std::vector<int>();
        outboundMap[i] = std::vector<int>();
    }
}

int Graph::nrNodes() {
    return (int)(outboundMap.size());
}

int Graph::nrArcs() {
    return (int)(costMap.size());
}

std::pair<std::map<int, std::vector<int>>::iterator , std::map<int, std::vector<int>>::iterator> Graph::setOfNodes() {
    return std::make_pair(outboundMap.begin(), outboundMap.end());
}

bool Graph::isNode(int v) {
    return inboundMap.find(v) != inboundMap.end();
}

bool Graph::isArc(int v1, int v2) {
    return std::find(outboundMap[v1].begin(), outboundMap[v1].end(), v2) != outboundMap[v1].end();
}

void Graph::addArc(int v1, int v2, int cost) {
    if (!isNode(v1) || !isNode(v2) || isArc(v1, v2)) {
        throw std::exception();
    }
    costMap[std::make_pair(v1, v2)] = cost;
    outboundMap[v1].push_back(v2);
    inboundMap[v2].push_back(v1);
}

int Graph::inDegree(int x) {
    return (int)(inboundMap[x].size());
}

int Graph::outDegree(int x) {
    return (int)(outboundMap[x].size());
}

std::pair <std::vector<int>::iterator, std::vector<int>::iterator> Graph::inboundArc(int x) {
    return std::make_pair(inboundMap[x].begin(), inboundMap[x].end());
}

std::pair<std::vector<int>::iterator, std::vector<int>::iterator> Graph::outboundArc(int x) {
    return std::make_pair(outboundMap[x].begin(), outboundMap[x].end());
}

void Graph::changeCost(int x, int y, int val) {
    if (!isArc(x, y)) {
        throw std::exception();
    }
    this->costMap[std::make_pair(x, y)] = val;
}

int Graph::getCost(int x, int y) {
    if (!isArc(x, y)) {
        throw std::exception();
    }
    return costMap[std::make_pair(x, y)];
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
    inboundMap[y].erase(std::find(inboundMap[y].begin(), inboundMap[y].end(), x));
    outboundMap[x].erase(std::find(outboundMap[x].begin(), outboundMap[x].end(), y));
}

void Graph::addNode(int val) {
    if (isNode(val)) {
        throw std::exception();
    }
    inboundMap[val] = std::vector<int>();
    outboundMap[val] = std::vector<int>();
}

void Graph::removeNode(int val) {
    inboundMap.erase(inboundMap.find(val));
    outboundMap.erase(outboundMap.find(val));
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
    std::map<int, std::vector<int>> newInMap;
    for (auto el : inboundMap) {
        auto c = std::find(el.second.begin(), el.second.end(), val);
        if (c != el.second.end()) {
            el.second.erase(c);
        }
    }
    for (int i = 0; i < inboundMap.size(); ++i) {
        int x = i;
        if (x > val) --x;
        newInMap[x] = inboundMap[i];
        for (int j = 0; j < inboundMap[i].size(); ++j) {
            if (inboundMap[i][j] > val) {
                newInMap[x][j] = inboundMap[i][j] - 1;
            }
        }
    }
    std::map<int, std::vector<int>> newOutMap;
    for (auto el : outboundMap) {
        auto c = std::find(el.second.begin(), el.second.end(), val);
        if (c != el.second.end()) {
            el.second.erase(c);
        }
    }
    for (int i = 0; i < outboundMap.size(); ++i) {
        int x = i;
        if (x > val) --x;
        newOutMap[x] = outboundMap[i];
        for (int j = 0; j < outboundMap[i].size(); ++j) {
            if (outboundMap[i][j] > val) {
                newOutMap[x][j] = outboundMap[i][j] - 1;
            }
        }
    }
    std::cout << std::endl;
    inboundMap = newInMap;
    outboundMap = newOutMap;
}

std::string Graph::toString() {
    std::string str;
    str += std::to_string(nrNodes()) + " " + std::to_string(nrArcs()) + "\n";
    for (auto i: costMap) {
        str += std::to_string(i.first.first) + " " + std::to_string(i.first.second) + " " + std::to_string(i.second) + "\n";
    }
    return str;
}
