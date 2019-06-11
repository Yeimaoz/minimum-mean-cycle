#include "Graph.h"
#include <algorithm>
#include <iomanip>
using std::cout;
using std::cin;
using std::sort;
using std::setw;

//----------------------------------------------------------------------------------------------------------------------
Graph::Graph(vector<node_S*> nodes, vector<edge_S*> edges){
    _super = new Node(0);
    // new node
    for (auto it = nodes.begin(); it != nodes.end(); ++it){
        _nodes[(*it)->_id] = new Node((*it)->_id);
        _super->append(-1, _super, _nodes[(*it)->_id], 0);
    }
    // append edge to node
    int edge_id = 1;
    for (auto it = edges.begin(); it != edges.end(); ++it){
        _nodes[(*it)->_fromNode]->append(edge_id, _nodes[(*it)->_fromNode], _nodes[(*it)->_toNode], (*it)->_weight);
        _edges.push_back(_nodes[(*it)->_fromNode]->_fanouts.back());
        ++edge_id;
    }
}
//----------------------------------------------------------------------------------------------------------------------
Graph::~Graph(){
    // delete nodes
    for (auto it = _nodes.begin(); it != _nodes.end(); ++it){
        delete it->second;
    }
    delete _super;
}
//----------------------------------------------------------------------------------------------------------------------
void Graph::information(const char* hierachy){
    cout << "Show graph information ..." << endl;
    cout << hierachy << "Nodes: " << _nodes.size() << endl;
    cout << hierachy << "Edges: " << _edges.size() << endl;
}
//----------------------------------------------------------------------------------------------------------------------
Node* Graph::find(int id){
    auto it = _nodes.find(id);
    return it == _nodes.end() ? NULL : it->second;
}
//----------------------------------------------------------------------------------------------------------------------
void Graph::minimum_mean_cycle(){
    // karp's algorithm 
    single_source_shortest_path();
    // d_information();
    size_t size = _nodes.size()+1; // contains super node
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
    // cout << _d_path[rj][ri].size() << " " << _d_path[size][ri].size() << endl;
    // for (auto edge : _d_path[rj][ri]) {edge->information();}
    // cout << "??" << endl;
    // for (auto edge : _d_path[size][ri]) {edge->information();}
}
//----------------------------------------------------------------------------------------------------------------------
void Graph::single_source_shortest_path(){
    vector<Node*> nodes;
    nodes.push_back(_super);
    for(auto& p : _nodes){nodes.push_back(p.second);}
    vector<vector<list<int>>> d_path(nodes.size()+1, vector<list<int>>(nodes.size()));
    vector<vector<int>> d(nodes.size()+1, vector<int>(nodes.size(), 1e9));
    d[0][0] = 0;
    for (size_t k=1; k <= nodes.size(); ++k){
        for (size_t i=0; i < nodes.size(); ++i){
            for (auto edge : nodes[i]->_fanins){ 
                int cur = d[k-1][edge->_from->_id] + edge->_weight; 
                if (cur < d[k][i]){
                    d[k][i] = cur;
                    // auto temp = d_path[k-1][edge->_from->_id];
                    // temp.push_back(edge->_to->_id);
                    // d_path[k][i] = temp;
                } 
            }
        }
    }
    _d = d;
    _d_path = d_path;
}
//----------------------------------------------------------------------------------------------------------------------
void Graph::d_information(){
    size_t _setw = 5;
    cout << "     "; for (size_t i = 0; i < _nodes.size()+1; ++i){ cout << setw(_setw) << i;} cout << endl;
    for (size_t i = 0; i < _d.size(); ++i){
        cout << setw(_setw) << (i != 0 ? to_string(i-1) : "*"); 
        for (size_t j = 0 ; j < _d[i].size(); ++j){
            cout << setw(_setw) << (_d[i][j] == 1e9 ? "*" : to_string(_d[i][j]));
        }
        cout << endl;
    }
}
//----------------------------------------------------------------------------------------------------------------------