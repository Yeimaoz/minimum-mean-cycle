#include "Graph.h"
using std::cout;
using std::cin;
using std::sort;
using std::setw;

//----------------------------------------------------------------------------------------------------------------------
Graph::Graph(vector<node_S*> nodes, vector<edge_S*> edges){
    nc = nodes.size();
    ec = edges.size();
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
void Graph::Karp_Algorithm(){
    single_source_shortest_path();
    // table_information(_d);
    // table_information(_f);
    size_t size = _nodes.size(); // contains super node

    int ri = -1;
    int rj = -1;
    int _i = -1;
    int _j = -1;
    for (size_t i = 0; i < size; ++i){ 
        if (_d[size][i] == 1e9) continue;
        double average = -1e9; 
        for (size_t j = 0; j < size; j++) {
            if (_d[j][i] == 1e9) continue;
            double avg = ((double)_d[size][i]-_d[j][i])/(size-j);
            if (avg > average) {
                _i = i, _j = j;
                average = avg;
            }
        }
        if (average < _minimum_mean){
            ri = _i, rj = _j;
            _minimum_mean = average;
        }
    } 
    if (_minimum_mean == 1e9) return; // acyclic

    auto p1 = back_trace(size, ri);
    auto p2 = back_trace(rj, ri);
    minimum_mean_cycle(p1, p2);
}
//----------------------------------------------------------------------------------------------------------------------
void Graph::single_source_shortest_path(){
    vector<vector<int>> f(_nodes.size()+1, vector<int>(_nodes.size(), -1));
    vector<vector<int>> d(_nodes.size()+1, vector<int>(_nodes.size(), 1e9));
    d[0][0] = 0;
    for (size_t k = 1; k <= _nodes.size(); ++k){
        for (size_t i = 0; i < _nodes.size(); ++i){
            for (auto edge : _edges[i]){ 
                int cur = d[k-1][edge->_fromNode] + edge->_weight; 
                if (cur < d[k][i]){
                    d[k][i] = cur;
                    f[k][i] = edge->_fromNode;
                }
            }
        }
    }
    _d = d, _f = f;
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
void Graph::minimum_mean_cycle(vector<int>& lhs, vector<int>& rhs){
    vector<int> _lhs(lhs.rbegin(), lhs.rend());
    int begin = -1;
    int end = rhs.size();
    for (unsigned int j = 0; j < rhs.size(); ++j){
        if (lhs[j] != rhs[j]){
            end = j;
            break;
        }
    }
    begin = rhs.size()-end;
    end = lhs.size()-end;
    int flag = _lhs[begin];
    for (int i = begin+1; i < end+1; ++i){
        if (flag == _lhs[i]){
            _minimum_mean_cycle.assign(next(_lhs.begin(), begin), next(_lhs.begin(), i+1));
            for (auto n : _minimum_mean_cycle){ _minimum_mean_cycle_s += to_string(n) + " ";}
            break;
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------
void Graph::solution(){
    if (_minimum_mean == 1e9){
        printf("[case info] #node:%d, #edge:%d\n", nc, ec);
        printf("[my solution] MMC: %.2f\n", _minimum_mean);
        printf("[my solution] Cycle: %s\n", "no cycle");
    } else {
        printf("[case info] #node:%d, #edge:%d\n", nc, ec);
        printf("[my solution] MMC: %.2f\n", _minimum_mean);
        printf("[my solution] Cycle: %s\n", _minimum_mean_cycle_s.c_str());
    }
}
//----------------------------------------------------------------------------------------------------------------------
void Graph::dump(){
    ofstream outfile("solution.txt", ios::out);

    if (_minimum_mean != 1e9){
        // have cycle
        outfile << fixed << setprecision(2) << _minimum_mean << endl;
        outfile <<_minimum_mean_cycle_s << endl;
    } else {
        // acyclic
        outfile << "No cycle" << endl;;
    }
    outfile.close();
}
//----------------------------------------------------------------------------------------------------------------------