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

class Strongly_Connected_Component{
    public:
        Strongly_Connected_Component(vector<Edge*> scc): _scc(scc){}
        vector<Edge*> _scc;
};

#endif