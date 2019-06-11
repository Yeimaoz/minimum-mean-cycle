#ifndef __NODE_H__
#define __NODE_H__
#include <vector>
#include <iostream>
using namespace std;
class Node;
class Edge;

class Node{
    public:
        // constructor, copy constructor, destructor
        Node(int id): _id(id) {}
        Node(const Node&);
        ~Node();
        
        // get
        void information();

        // action
        void append(int id, Node* from, Node* to, int weight);
        
        // attribute
        int _id;
        vector<Edge*> _fanouts;
        vector<Edge*> _fanins;
};

class Edge{
    public:
        // constructor, copy constructor, destructor
        Edge(int id, Node* from, Node* to, int weight): _id(id), _from(from), _to(to), _weight(weight){}
        Edge(const Edge& in): _id(in._id), _from(in._from), _to(in._to), _weight(in._weight){}
        void information(){  cout << "from " << _from->_id << " to " << _to->_id << " (" << _weight << ")"<< endl; }

        // attribute
        int _id;
        Node* _from;
        Node* _to;
        int _weight;
};

#endif