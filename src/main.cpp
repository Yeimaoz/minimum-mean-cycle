#include <iostream>
#include "parser.h"
#include "Graph.h"
using namespace std;

int main(int argc, char** argv) 
{
    if(argc < 2){
        printf("Usage: ./Lab1 <.in>\n");
        return 0;
    }
    
    parser_S* pParser;
    if (argc == 2) {
        pParser = new parser_S(argv[1]);
        pParser->parse();
        pParser->dump();
    } else if (argc == 3) { //verifier
        pParser = new parser_S(argv[1], argv[2]);
        if (!pParser->parse()) {
            return 0;
        }
        pParser->dump();
    }

    Graph* G = new Graph(pParser->_vNode, pParser->_vEdge);
    G->Karp_Algorithm();
    G->solution();
    G->dump();

    delete G;
    delete pParser;
    return 0;
}