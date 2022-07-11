//
// Created by andre on 03/04/2022.
//

#ifndef PRACTICAL2_GRAPH_H
#define PRACTICAL2_GRAPH_H


#include <map>
#include <utility>
#include <list>
#include <vector>
#include <string>
#include <exception>


class Graph {
private:
    std::map<int, std::vector<int>> arcsMap;
    std::map<std::pair<int, int>, int> costMap;

    void DFS(int currentNode, bool *visited, std::list<int>& component);
public:
    // constructor
    explicit Graph(int nrVertices);

    int nrNodes();
    // returns the number of nodes

    int nrArcs();
    // returns the number of arcs

    std::pair<std::map<int, std::vector<int>>::iterator , std::map<int, std::vector<int>>::iterator> setOfNodes();
    // returns a pair of 2 maps that contain the nodes and their arcs so the graph can be crated

    bool isNode(int v);
    // returns true if the value v is a node, false if not

    bool isArc(int v1, int v2);
    // returns true if the v1 and v2 make a valid arc, else it returns false

    void addArc(int v1, int v2, int cost);
    // adds an arc between the v1 and v2 nodes with the cost 'cost'

    int arcDegree(int x);
    // returns the degree of arcs from the node x

    std::pair <std::vector<int>::iterator, std::vector<int>::iterator> arcList(int x);
    // returns a pair of the vector containing all outbound arcs from the node x

    void changeCost(int x, int y, int val);
    // changes the cost of the arc between the nodes x and y

    int getCost(int x, int y);
    // returns the cost of the arc between the nodes x and y

    void removeArc(int x, int y);
    // removes the arc between the nodes x and y

    void addNode(int val);
    // adds a node val

    void removeNode(int val);
    // removes the node val

    std::string toString();
    // returns the graph in a string

    std::list<std::list<int>> connectedComponents();
    // returns a list of all connected components as lists of ints
};

#endif //PRACTICAL2_GRAPH_H
