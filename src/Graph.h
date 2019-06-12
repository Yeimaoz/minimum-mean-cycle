#ifndef __GRAPH_H__
#define __GRAPH_H__
#include <iostream>
#include <map>
#include <string>
#include <list>
#include "parser.h"
#include "Node.h"
using std::map;
using std::cout;
using std::cin;
using std::string;

class Graph{
    public:
        // constructor, destructor
        Graph();
        Graph(vector<node_S*> nodes, vector<edge_S*> edges);
        ~Graph();

        // get
        void information(const char* hierachy="- ");
        void table_information(vector<vector<int>>&);

        // action
        void minimum_mean_cycle();
        void single_source_shortest_path();
        vector<int> back_trace(int, int);


    private:
        // attribute
        // G
        // map<int, Node*> _nodes;
        // vector<Edge*> _edges;
        Node* _super;

        vector<node_S*> _nodes;
        vector<vector<edge_S*>> _edges;

        vector<vector<int>> _d;
        vector<vector<int>> _f;
        vector<vector<list<int>>> _d_path;
};
#endif