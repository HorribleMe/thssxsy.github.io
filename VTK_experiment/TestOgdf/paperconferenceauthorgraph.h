#ifndef PAPERCONFERENCEAUTHORGRAPH
#define PAPERCONFERENCEAUTHORGRAPH
#include <string>

using namespace std;

class Node
{
public:
    Node(){}
    ~Node(){}
    int m_num;
    string m_type;
    int m_year;
    string m_ID;
    int m_viewColor[4];
    string m_viewLabel;
    double m_viewLayout[2];
};

class Pnode: public Node
{
public:
    Pnode(){}
    ~Pnode(){}
    string m_author;
    int m_dataFrom;
    int m_pageFrom;
    string m_paperTitle;
    string m_shortTitle;
};

class Cnode: public Node
{
public:
    Cnode(){}
    ~Cnode(){}
    string m_conferenceName;
    string m_shortName;
};

class Anode: public Node
{
public:
    Anode(){}
    ~Anode(){}
    string m_authorName;
    string m_shortAuthorName;
};

class Pedge
{
public:
    Pedge(){}
    ~Pedge(){}
    int m_node1;
    int m_node2;
};

class Pgraph
{
public:
    Pgraph(){}
    ~Pgraph(){}
    Pedge m_edge[900];
    Pnode m_pnode[200];
    Anode m_anode[100];
    Cnode m_cnode[100];
    int pnumber;
    int anumber;
    int cnumber;
    int edgeNumber;
    void createPgraph();
    void optimizate();
};
#endif // PAPERCONFERENCEAUTHORGRAPH

