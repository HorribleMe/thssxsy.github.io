#include "topicgraph.h"
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

void Tgraph::createTgraph()
{
    ifstream getNodes("/Users/THSS-XSY/Documents/QtProjects/TestOgdf/GraphData/TopicGraph/Nodes.txt",  ios::in);
    nodeNumber = edgeNumber = passageNumber = 0;
    int i = 0;
    int k;
    string temSave;
    if(!getNodes)
        cout << "error";
    while(!getNodes.eof())
    {
        for (k = 0; k < 3; k++)
        {
            if (k == 2)
            getline(getNodes, m_nodes[i].m_DocumentID);
            else if(k == 1)
            getline(getNodes, m_nodes[i].m_TopicWords);
            else
            {
                getline(getNodes, temSave);
                m_nodes[i].m_ID = atoi(temSave.c_str());
            }
        }
        getline(getNodes, temSave);
        i++;
        nodeNumber++;
    }
    ifstream getEdges("/Users/THSS-XSY/Documents/QtProjects/TestOgdf/GraphData/TopicGraph/Edges.txt",  ios::in);
    i = 0;
    while(!getEdges.eof())
    {
        for(int k = 0; k < 3;k++)
        {
            if(k == 0)
            getEdges >> m_edges[i].m_NodeID1;
            else if(k == 1)
            getEdges >> m_edges[i].m_NodeID2;
            else
            getEdges >> m_edges[i].m_Attribute;
        }
        i++;
        edgeNumber++;
    }
    ifstream getDoc("/Users/THSS-XSY/Documents/QtProjects/TestOgdf/GraphData/TopicGraph/DocumentContent.txt",  ios::in);
    i = 0;
    while(!getDoc.eof())
    {
        for(k = 0;k < 3;k++)
        {
            if(k == 0)
            {
                getline(getDoc, temSave);
                m_passages[i].m_ID = atoi(temSave.c_str());
            }
            else if(k == 1)
            {
                getline(getDoc, temSave);
                m_passages[i].m_Title = temSave;
            }
            else
                getline(getDoc, m_passages[i].m_Content);
        }
        getline(getDoc, temSave);
        i++;
        passageNumber++;
    }
    nodeNumber--;
    edgeNumber--;
    passageNumber--;
    return;
}

void Tgraph::optimizate()
{
    bool sign1 = false;
    bool sign2 = false;
    for (int i = 0; i < edgeNumber; i++)
    {
        for (int j = 0; j < nodeNumber; j++)
        {
            if (m_edges[i].m_NodeID1 == m_nodes[j].m_ID)
            {
                m_edges[i].m_NodeID1 = j;
                sign1 = true;
            }
            if (m_edges[i].m_NodeID2 == m_nodes[j].m_ID)
            {
                m_edges[i].m_NodeID2 = j;
                sign2 = true;
            }
            if (sign1 == true && sign2 == true) {
                break;
            }
        }
        sign1 = false;
        sign2 = false;
    }
    return;
}


