#include "paperconferenceauthorgraph.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

void Pgraph::createPgraph()
{
    ifstream getNodes("/Users/THSS-XSY/Documents/QtProjects/TestOgdf/GraphData/PaperConferenceAuthorGraph/Nodes.txt",  ios::in);
    string temSave1, temSave2;
    anumber = pnumber = cnumber = 0;
    if (!getNodes) {
        cout << "error";
    }
    while(!getNodes.eof())
    {
        getline(getNodes, temSave1);
        getline(getNodes, temSave2);
        if(temSave2 == "type: paper\r")
        {
            m_pnode[pnumber].m_num = atoi(temSave1.c_str());
            m_pnode[pnumber].m_type = "paper";
            getline(getNodes, temSave1);
            temSave1.erase(0, 6);
            m_pnode[pnumber].m_year = atoi(temSave1.c_str());
            getline(getNodes, temSave1);
            temSave1.erase(0, 9);
            m_pnode[pnumber].m_author = temSave1;
            getline(getNodes, temSave1);
            temSave1.erase(0, 10);
            m_pnode[pnumber].m_dataFrom = atoi(temSave1.c_str());
            getline(getNodes, temSave1);
            temSave1.erase(0, 4);
            m_pnode[pnumber].m_ID = temSave1;
            getline(getNodes, temSave1);
            temSave1.erase(0, 10);
            m_pnode[pnumber].m_pageFrom = atoi(temSave1.c_str());
            getline(getNodes, temSave1);
            temSave1.erase(0, 12);
            m_pnode[pnumber].m_paperTitle = temSave1;
            getline(getNodes, temSave1);
            temSave1.erase(0, 17);
            m_pnode[pnumber].m_shortTitle = temSave1;
            getNodes >> temSave1;
            getNodes.seekg(2, ios::cur);
            getNodes >> m_pnode[pnumber].m_viewColor[0];
            getNodes.seekg(1, ios::cur);
            getNodes >> m_pnode[pnumber].m_viewColor[1];
            getNodes.seekg(1, ios::cur);
            getNodes >> m_pnode[pnumber].m_viewColor[2];
            getNodes.seekg(1, ios::cur);
            getNodes >> m_pnode[pnumber].m_viewColor[3];
            getline(getNodes, temSave1);
            getline(getNodes, temSave1);
            temSave1.erase(0, 11);
            m_pnode[pnumber].m_viewLabel = temSave1;
            getNodes >> temSave1;
            getNodes.seekg(2, ios::cur);
            getNodes >> m_pnode[pnumber].m_viewLayout[0];
            getNodes.seekg(1, ios::cur);
            getNodes >> m_pnode[pnumber].m_viewLayout[1];
            pnumber++;
        }
        else if(temSave2 == "type: conference\r")
        {
            m_cnode[cnumber].m_num = atoi(temSave1.c_str());
            m_cnode[cnumber].m_type = "conference";
            getline(getNodes, temSave1);
            temSave1.erase(0, 6);
            m_cnode[cnumber].m_year = atoi(temSave1.c_str());
            getline(getNodes, temSave1);
            temSave1.erase(0, 4);
            m_cnode[cnumber].m_ID = temSave1;
            getline(getNodes, temSave1);
            temSave1.erase(0, 16);
            m_cnode[cnumber].m_conferenceName = temSave1;
            getline(getNodes, temSave1);
            temSave1.erase(0, 21);
            m_cnode[cnumber].m_shortName = temSave1;
            getNodes >> temSave1;
            getNodes.seekg(2, ios::cur);
            getNodes >> m_cnode[cnumber].m_viewColor[0];
            getNodes.seekg(1, ios::cur);
            getNodes >> m_cnode[cnumber].m_viewColor[1];
            getNodes.seekg(1, ios::cur);
            getNodes >> m_cnode[cnumber].m_viewColor[2];
            getNodes.seekg(1, ios::cur);
            getNodes >> m_cnode[cnumber].m_viewColor[3];
            getline(getNodes, temSave1);
            getline(getNodes, temSave1);
            temSave1.erase(0, 11);
            m_cnode[cnumber].m_viewLabel = temSave1;
            getNodes >> temSave1;
            getNodes.seekg(2, ios::cur);
            getNodes >> m_cnode[cnumber].m_viewLayout[0];
            getNodes.seekg(1, ios::cur);
            getNodes >> m_cnode[cnumber].m_viewLayout[1];
            cnumber++;
        }
        else if(temSave2 == "type: author\r")
        {
            m_anode[anumber].m_num = atoi(temSave1.c_str());
            m_anode[anumber].m_type = "author";
            getline(getNodes, temSave1);
            temSave1.erase(0, 6);
            m_anode[anumber].m_year = atoi(temSave1.c_str());
            getline(getNodes, temSave1);
            temSave1.erase(0, 4);
            m_anode[anumber].m_ID = temSave1;
            getline(getNodes, temSave1);
            temSave1.erase(0, 12);
            m_anode[anumber].m_authorName = temSave1;
            getline(getNodes, temSave1);
            temSave1.erase(0, 17);
            m_anode[anumber].m_shortAuthorName = temSave1;
            getNodes >> temSave1;
            getNodes.seekg(2, ios::cur);
            getNodes >> m_anode[anumber].m_viewColor[0];
            getNodes.seekg(1, ios::cur);
            getNodes >> m_anode[anumber].m_viewColor[1];
            getNodes.seekg(1, ios::cur);
            getNodes >> m_anode[anumber].m_viewColor[2];
            getNodes.seekg(1, ios::cur);
            getNodes >> m_anode[anumber].m_viewColor[3];
            getline(getNodes, temSave1);
            getline(getNodes, temSave1);
            temSave1.erase(0, 11);
            m_anode[anumber].m_viewLabel = temSave1;
            getNodes >> temSave1;
            getNodes.seekg(2, ios::cur);
            getNodes >> m_anode[anumber].m_viewLayout[0];
            getNodes.seekg(1, ios::cur);
            getNodes >> m_anode[anumber].m_viewLayout[1];
            anumber++;
        }
        getline(getNodes, temSave2);
        getline(getNodes, temSave2);
    }
    ifstream getEdges("/Users/THSS-XSY/Documents/QtProjects/TestOgdf/GraphData/PaperConferenceAuthorGraph/Edges.txt");
    edgeNumber = 0;
    while(!getEdges.eof())
    {
        for(int k = 0;k < 2;k++)
        {
            if(k == 0)
                getEdges >> m_edge[edgeNumber].m_node1;
            else
                getEdges >> m_edge[edgeNumber].m_node2;
        }
        edgeNumber++;
    }
    edgeNumber--;
    return;
}

void Pgraph::optimizate()
{
    bool sign1 = false;
    bool sign2 = false;
    for (int i = 0; i < edgeNumber; i++)
    {
        int j = 0;
        for (; j < pnumber; j++)
        {
            if (m_edge[i].m_node1 == m_pnode[j].m_num)
            {
                m_edge[i].m_node1 = j;
                sign1 = true;
            }
            if (m_edge[i].m_node2 == m_pnode[j].m_num)
            {
                m_edge[i].m_node2 = j;
                sign2 = true;
            }
            if(sign1 == true && sign2 == true)
                break;
        }
        if(sign1 == false || sign2 == false)
        {
            for(int p = 0; p < cnumber;j++, p++)
            {
                if (m_edge[i].m_node1 == m_cnode[p].m_num)
                {
                    m_edge[i].m_node1 = j;
                    sign1 = true;
                }
                if (m_edge[i].m_node2 == m_cnode[p].m_num)
                {
                    m_edge[i].m_node2 = j;
                    sign2 = true;
                }
                if (sign1 == true && sign2 == true) {
                    break;
                }
            }
        }
        if(sign1 == false || sign2 == false)
        {
            for(int a = 0; a < anumber;j++, a++)
            {
                if (m_edge[i].m_node1 == m_anode[a].m_num)
                {
                    m_edge[i].m_node1 = j;
                    sign1 = true;
                }
                if (m_edge[i].m_node2 == m_anode[a].m_num)
                {
                    m_edge[i].m_node2 = j;
                    sign2 = true;
                }
                if (sign1 == true && sign2 == true) {
                    break;
                }
            }
        }
        sign1 = false;
        sign2 = false;
    }
    return;
}


