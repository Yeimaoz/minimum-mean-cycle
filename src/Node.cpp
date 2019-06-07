#include "Node.h"
#include <iostream>
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
Node::Node(const Node& in){
    _id = in._id;
    _d = in._d;
    _f = in._f;
    _visited= in._visited;
    _fanouts = in._fanouts;
    _fanouts_it = in._fanouts_it;
}
//----------------------------------------------------------------------------------------------------------------------
Node::~Node(){
    for (auto it = _fanouts.begin(); it != _fanouts.end(); ++it){
        delete *it;
    }
}
//----------------------------------------------------------------------------------------------------------------------
void Node::information(){
    cout << "Node: " << _id << endl;
    cout << "Discovered time: " << _d << endl;
    cout << "Finished time: " << _f << endl;
    cout << "Fanouts: ";
    for (auto it = _fanouts.begin(); it != _fanouts.end(); ++it){
        cout << (*it)->_to->_id << "(" << (*it)->_weight << ") ";
    }
    cout << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void Node::append(int id, Node* to, int weight){
    _fanouts.push_back(new Edge(id, to, weight));
}
//----------------------------------------------------------------------------------------------------------------------