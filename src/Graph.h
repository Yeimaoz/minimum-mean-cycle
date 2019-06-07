#ifndef __GRAPH_H__
#define __GRAPH_H__
#include <iostream>
#include <map>
#include "parser.h"
#include "Node.h"
using namespace std;

class Graph;
class Strongly_Connected_Component;

class Graph{
    public:
        // constructor, destructor
        Graph();
        Graph(vector<node_S*> nodes, vector<edge_S*> edges);
        ~Graph();

        // get
        void information(const char* hierachy="- ");
        Node* find(int);

        // action
        void depth_first_search();
        void find_strongly_connected_components();
        void find_all_cycles();

    private:
        // attribute
        // G
        map<int, Node*> _nodes;
        Node* _super;
        // T
        map<int, Node*> T_nodes;
        Node* T_super;
        vector<Strongly_Connected_Component*> _sccs;
};

class Cycle{
    public:
        Cycle(vector<Edge*> cycle): _cycle(cycle){}
        vector<Edge*> _cycle;
        void information() { for(auto it = _cycle.begin(); it != _cycle.end(); ++it) {cout << (*it)->_to->_id << " ";} cout << endl;};
};

#endif