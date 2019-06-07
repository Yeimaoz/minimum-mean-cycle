#ifndef __NODE_H__
#define __NODE_H__
#include <vector>
using namespace std;
class Node;
class Edge;

class Node{
    public:
        // constructor, copy constructor, destructor
        Node(int id): _id(id), _d(-1), _f(-1), _visited(false) {}
        Node(const Node&);
        ~Node();
        
        // get
        void information();

        // action
        void append(int id, Node* to, int weight);
        
        // attribute
        int _id;
        int _d;
        int _f;
        bool _visited;
        vector<Edge*> _fanouts;
        vector<Edge*>::iterator _fanouts_it;
};

class Edge{
    public:
        // constructor, copy constructor, destructor
        Edge(int id, Node* to, int weight): _id(id), _to(to), _weight(weight){}
        Edge(const Edge& in): _to(in._to), _weight(in._weight){}

        // attribute
        int _id;
        Node* _to;
        int _weight;
};

#endif