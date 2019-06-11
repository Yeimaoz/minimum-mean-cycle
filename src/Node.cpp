#include "Node.h"
#include <iostream>
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
Node::Node(const Node& in){
    _id = in._id;
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
    cout << "Fanouts: ";
    for (auto it = _fanouts.begin(); it != _fanouts.end(); ++it){
        cout << (*it)->_to->_id << "(" << (*it)->_weight << ") ";
    }
    cout << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void Node::append(int id, Node* from, Node* to, int weight){
    _fanouts.push_back(new Edge(id, from, to, weight));
    to->_fanins.push_back(new Edge(id, from, to, weight));
}
//----------------------------------------------------------------------------------------------------------------------