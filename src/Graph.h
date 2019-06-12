#ifndef __GRAPH_H__
#define __GRAPH_H__
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>
#include <iomanip>
#include "parser.h"
using namespace std;

class Graph{
    public:
        // constructor, destructor
        Graph();
        Graph(vector<node_S*> nodes, vector<edge_S*> edges);
        ~Graph();

        // get
        void information(const char* hierachy="- ");
        void table_information(vector<vector<int>>&);
        void solution();
        void dump();

        // action
        void Karp_Algorithm();
        void single_source_shortest_path();
        void minimum_mean_cycle(vector<int>&, vector<int>&);
        vector<int> back_trace(int, int);


    private:
        // attribute
        int nc = -1; // node count
        vector<node_S*> _nodes;
        int ec = -1; // edge count
        vector<vector<edge_S*>> _edges;

        // solution
        double _minimum_mean = 1e9;
        vector<int> _minimum_mean_cycle;
        string _minimum_mean_cycle_s = "";
        
        // table for dynamic programming
        vector<vector<int>> _d;
        vector<vector<int>> _f;
};
#endif