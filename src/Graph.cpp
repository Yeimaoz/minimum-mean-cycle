#include "Graph.h"
#include <algorithm>

//----------------------------------------------------------------------------------------------------------------------
Graph::Graph(vector<node_S*> nodes, vector<edge_S*> edges){
    _super = new Node(-1);
    T_super = new Node(-1);
    // new node
    for (auto it = nodes.begin(); it != nodes.end(); ++it){
        _nodes[(*it)->_id] = new Node((*it)->_id);
        _super->append(_nodes[(*it)->_id], 0);
        T_nodes[(*it)->_id] = new Node((*it)->_id);
        T_super->append(T_nodes[(*it)->_id], 0);
    }
    // append edge to node
    for (auto it = edges.begin(); it != edges.end(); ++it){
        _nodes[(*it)->_fromNode]->append(_nodes[(*it)->_toNode], (*it)->_weight);
        T_nodes[(*it)->_toNode]->append(T_nodes[(*it)->_fromNode], (*it)->_weight);
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
}
//----------------------------------------------------------------------------------------------------------------------
Node* Graph::find(int id){
    auto it = _nodes.find(id);
    return it == _nodes.end() ? NULL : it->second;
}
//----------------------------------------------------------------------------------------------------------------------
void Graph::depth_first_search(){
    cout << "Depth first searching ..." << endl;
    _super->_fanouts_it = _super->_fanouts.begin();
    for_each(_super->_fanouts.begin(),_super->_fanouts.end(), [](Edge* edge) {edge->_to->_fanouts_it = edge->_to->_fanouts.begin();});
    vector<Node*> stack;
    stack.push_back(_super);
    int time = _super->_d = 0;
    while (!stack.empty()){
        Node* top = stack.back(); 
        // cout << "id: " << top->_id << " fanouts: " << top->_fanouts.size() << " d: " << top->_d << " f: " << top->_f << endl;
        // cout << stack.size() << endl;
        // cin.get();
        if (top->_fanouts_it == top->_fanouts.end()) { 
            top->_f = ++time;
            stack.pop_back(); 
        } else {
            if (!(*top->_fanouts_it)->_to->_visited){
                (*top->_fanouts_it)->_to->_visited = true;
                (*top->_fanouts_it)->_to->_d = ++time;
                stack.push_back((*top->_fanouts_it++)->_to);
            } else {
                ++top->_fanouts_it;
            }
        }      
    }
}
//----------------------------------------------------------------------------------------------------------------------
void Graph::find_strongly_connected_components(){
    cout << "Finding strongly connected components ..." << endl;
    struct cmp {
        cmp(map<int, Node*>* lut) { this->lut = lut; }
        bool operator () (const Edge* lhs, const Edge* rhs) { return (*this->lut)[lhs->_to->_id]->_f < (*this->lut)[rhs->_to->_id]->_f; }
        map<int, Node*>* lut;
    };
    sort(T_super->_fanouts.begin(), T_super->_fanouts.end(), cmp(&_nodes));
 
    T_super->_fanouts_it = T_super->_fanouts.begin();
    for_each(T_super->_fanouts.begin(),T_super->_fanouts.end(), [](Edge* edge) {edge->_to->_fanouts_it = edge->_to->_fanouts.begin();});
    // vector<Node*> stack;
    // stack.push_back(T_super);
    
    // for (auto it = T_super->_fanouts.begin(); it != T_super->_fanouts.end(); ++it){
    //     vector<Edge*> ssc;
    //     auto start = (*it)->_to; 
    //     while( start->_fanouts_it != start->_fanouts.end() &&   )
    // }
    

    // while (!stack.empty()){
    //     Node* top = stack.back(); 
    //     // cout << "id: " << top->_id << " fanouts: " << top->_fanouts.size() << " d: " << top->_d << " f: " << top->_f << endl;
    //     // cout << stack.size() << endl;
    //     // cin.get();
    //     if (top->_fanouts_it == top->_fanouts.end()) { 
    //         top->_f = ++time;
    //         stack.pop_back(); 
    //     } else {
    //         if (!(*top->_fanouts_it)->_to->_visited){
    //             (*top->_fanouts_it)->_to->_visited = true;
    //             (*top->_fanouts_it)->_to->_d = ++time;
    //             stack.push_back((*top->_fanouts_it++)->_to);
    //         } else {
    //             ++top->_fanouts_it;
    //         }
    //     }      
    // }
}
//----------------------------------------------------------------------------------------------------------------------