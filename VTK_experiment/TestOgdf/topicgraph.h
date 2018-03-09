#ifndef TOPICGRAPH
#define TOPICGRAPH
#include <string>

using namespace std;

class Tnode
{
public:
    Tnode(){}
    ~Tnode(){}
    int m_ID;
    string m_DocumentID;
    string m_TopicWords;
};

class Tedge
{
public:
    Tedge(){}
    ~Tedge(){}
    int m_NodeID1;
    int m_NodeID2;
    double m_Attribute;
};

class Tpassage
{
public:
    Tpassage(){}
    ~Tpassage(){}
    int m_ID;
    string m_Title;
    string m_Content;
};

class Tgraph
{
public:
    Tgraph(){}
    ~Tgraph(){}
    Tnode m_nodes[200];
    Tedge m_edges[400];
    Tpassage m_passages[10000];
    int nodeNumber;
    int edgeNumber;
    int passageNumber;
    void createTgraph();
    void optimizate();
};
#endif // TOPICGRAPH

