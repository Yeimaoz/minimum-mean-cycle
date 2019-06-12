#include "Graph.h"
#include <algorithm>
#include <iomanip>
using std::cout;
using std::cin;
using std::sort;
using std::setw;

//----------------------------------------------------------------------------------------------------------------------
Graph::Graph(vector<node_S*> nodes, vector<edge_S*> edges){
    // reserve
    _nodes.resize(nodes.size()+1);
    _edges.resize(nodes.size()+1);
    // add super node
    _nodes[0] = new node_S(0);
    // new node
    for (auto node: nodes){
        _nodes[node->_id] = node;
        _edges[node->_id].push_back(new edge_S(0, node->_id, 0));
    }
    // _edges[i] : i's fanins ...
    for (auto edge: edges){
        _edges[edge->_toNode].push_back(edge);
    }
}
//----------------------------------------------------------------------------------------------------------------------
Graph::~Graph(){
    // delete nodes
    for (auto node: _nodes)
        delete node;
    for (auto edges: _edges){
        for (auto edge: edges)
            delete edge;
    }
}
//----------------------------------------------------------------------------------------------------------------------
void Graph::information(const char* hierachy){
    cout << "Show graph information ..." << endl;
    cout << hierachy << "Nodes: " << _nodes.size() << endl;
    cout << hierachy << "Edges: " << _edges.size() << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void Graph::minimum_mean_cycle(){
    // karp's algorithm 
    single_source_shortest_path();
    // table_information(_d);
    // table_information(_f);
    size_t size = _nodes.size(); // contains super node
    // vector<double> average(size, -1e9);

    double result = 1e9;
    int ri = -1;
    int rj = -1;
    int _i = -1;
    int _j = -1;
    for (size_t i = 0; i < size; ++i){ 
        if (_d[size][i] == 1e9) continue;
        double average = -1e9; 
        for (size_t j = 0; j < size; j++) {
            if (_d[j][i] == 1e9) continue;
            // cout << "size: " << size << " i: " << i << " j: " << j << endl;
            double avg = ((double)_d[size][i]-_d[j][i])/(size-j);
            // cout << "_d[size][i]: " << _d[size][i] << endl;
            // for (auto edge : _d_path[size][i]) {edge->information();}
            // cout << " _d[j][i]: " << _d[j][i] << endl;
            // for (auto edge : _d_path[j][i]) {edge->information();}
            // cout << "sub: " << (double)_d[size][i]-_d[j][i] << endl;
            // cout << "size-j: " << size-j << endl;
            // cout << avg <<endl;
            if (avg > average) {
                _i = i;
                _j = j;
                average = avg;
            }
        }
        if (average < result){
            ri = _i;
            rj = _j;
            result = average;
        }
    } 
    cout << ri << " " << rj << " " << result << endl;
    auto p1 = back_trace(size, ri);
    auto p2 = back_trace(rj, ri);
    cout << "p1.size: " << p1.size() << ", p2.size: " << p2.size() << endl;
    for (auto i : p1) {cout << i << " ";} cout << endl;
    for (auto i : p2) {cout << i << " ";} cout << endl;
    
}
//----------------------------------------------------------------------------------------------------------------------
void Graph::single_source_shortest_path(){
    // vector<Node*> nodes;
    // nodes.push_back(_super);
    // for(auto& p : _nodes){nodes.push_back(p.second);}
    // vector<vector<list<int>>> d_path(_nodes.size()+1, vector<list<int>>(_nodes.size()));
    vector<vector<int>> f(_nodes.size()+1, vector<int>(_nodes.size(), -1));
    vector<vector<int>> d(_nodes.size()+1, vector<int>(_nodes.size(), 1e9));
    cout << d.size() << " " << d[0].size() << endl;
    d[0][0] = 0;
    for (size_t k = 1; k <= _nodes.size(); ++k){
        for (size_t i = 0; i < _nodes.size(); ++i){
            // cout << "k: " << k << " i: " << i << endl;
            for (auto edge : _edges[i]){ 
                // edge->information();
                int cur = d[k-1][edge->_fromNode] + edge->_weight; 
                // cout << "d[" << k-1 << "][" << edge->_fromNode << "]: " << d[k-1][edge->_fromNode] << " w: " << edge->_weight << endl;
                // cout << "cur: " << cur;
                if (cur < d[k][i]){
                    d[k][i] = cur;
                    f[k][i] = edge->_fromNode;
                    // auto temp = d_path[k-1][edge->_fromNode];
                    // temp.push_back(edge->_toNode);
                    // d_path[k][i] = temp;
                } else{
                    }
            }
        }
    }
    _d = d;
    _f = f;
    // _d_path = d_path;
}
//----------------------------------------------------------------------------------------------------------------------
void Graph::table_information(vector<vector<int>>& table){
    size_t _setw = 3;
    cout << "   "; for (size_t i = 0; i < _nodes.size(); ++i){ cout << setw(_setw) << i;} cout << endl;
    for (size_t i = 0; i < table.size(); ++i){
        cout << setw(_setw) << i; 
        for (size_t j = 0 ; j < table[i].size(); ++j){
            cout << setw(_setw) << (table[i][j] == 1e9 ? "*" : to_string(table[i][j]));
        }
        cout << endl;
    }
}
//----------------------------------------------------------------------------------------------------------------------
vector<int> Graph::back_trace(int count, int dest){
    vector<int> path(1, dest);
    while(count > 1){
        dest = _f[count--][dest];
        path.push_back(dest);
    }
    return path;
}
//----------------------------------------------------------------------------------------------------------------------