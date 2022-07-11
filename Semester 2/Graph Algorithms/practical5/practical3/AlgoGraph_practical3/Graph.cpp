//
// Created by andrew on 02.05.2022.
//

#include "Graph.h"

Graph::Graph(int nrVertices) {
    for (int i = 0; i < nrVertices; ++i) {
        inboundMap[i] = std::vector<int>();
        outboundMap[i] = std::vector<int>();
    }
}

int Graph::nrNodes() {
    return (int) (outboundMap.size());
}

int Graph::nrArcs() {
    return (int) (costMap.size());
}

std::pair<std::map<int, std::vector<int>>::iterator, std::map<int, std::vector<int>>::iterator> Graph::setOfNodes() {
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
    if (this->inboundMap.find(x) == this->inboundMap.end())
        throw std::exception();
    return (int) (inboundMap[x].size());
}

int Graph::outDegree(int x) {
    if (this->outboundMap.find(x) == this->outboundMap.end())
        throw std::exception();
    return (int) (outboundMap[x].size());
}

std::pair<std::vector<int>::iterator, std::vector<int>::iterator> Graph::inboundArc(int x) {
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
    for (auto &elem: costMap) {
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
    if (!isNode(val)) {
        throw std::exception();
    }

    for (auto &elem: inboundMap[val])
        costMap.erase(costMap.find(std::make_pair(elem, val)));
    for (auto &elem: outboundMap[val])
        costMap.erase(costMap.find(std::make_pair(val, elem)));

    inboundMap.erase(inboundMap.find(val));
    outboundMap.erase(outboundMap.find(val));
}

std::string Graph::toString() {
    std::string str;
    str += std::to_string(nrNodes()) + " " + std::to_string(nrArcs()) + "\n";
    for (auto i: costMap) {
        str += std::to_string(i.first.first) + " " + std::to_string(i.first.second) + " " + std::to_string(i.second) +
               "\n";
    }
    return str;
}

std::pair<std::vector<int>, std::vector<int>> Graph::backwardsDijkstra(int source, int end) {
    // Checks if the nodes are valid
    if (!isNode(source) || !isNode(end)) {
        throw std::exception();
    }

    // Start from the end
//    source = end;

    // Declare a priority queue that will hold a pair (cost, node)
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> priorityQueue;

    // Declare the vector that will hold the smallest distance between the source and every node
    std::vector<int> dist(nrNodes(), INT32_MAX);

    // Declare the vector that will hold the path for all vertices
    std::vector<int> paths(nrNodes(), -1);

    // Initialise the queue and the distance vector
    priorityQueue.push(std::make_pair(0, source));
    dist[source] = 0;

    while (!priorityQueue.empty()) {
        int x = priorityQueue.top().second;  // x will hold the vertex number
        priorityQueue.pop();
        for (int y: outboundMap[x]) {  // Cycle through all inbound edges of x
            int cost = costMap[std::make_pair(x, y)];  // get the cost of the y->x edge

            if (dist[y] > dist[x] + cost) {  // Check if it is smaller than the current smallest distance
                dist[y] = dist[x] + cost;  // change the smallest cost
                paths[y] = x;  // update the shortest path
                priorityQueue.push(std::make_pair(dist[y], y));  // add the new node and the total cost to the queue
            }
        }
    }

    return std::make_pair(dist, paths);
}
