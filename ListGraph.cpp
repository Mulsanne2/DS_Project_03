#include "ListGraph.h"

ListGraph::ListGraph(bool type, int size) : Graph(type, size)
{
	m_Type = type;
	m_List = new map<int, int>[size];
	beforeFrom = -1;
}

ListGraph::~ListGraph()
{
	delete[] m_List;
}

void ListGraph::getAdjacentEdges(int vertex, map<int, int>* m)
{
	if(V[vertex]==NULL) //check if vertex doesn't have edge
		return;
	map<int, int>* temp = V[vertex]; //copy vector into m
	for (map<int, int>::iterator iter = temp->begin(); iter != temp->end();iter++)
		m->insert(pair<int, int>(iter->first, iter->second));
}

void ListGraph::insertEdge(int from, int to, int weight)
{
	int SIZE = V.size();
	//when before vector isn't connected which has only vertex
	while(V.size()<from){
		V.push_back(0);
	}

	if(from!=beforeFrom){ //when from is diffrent
		
		m_List[from].insert(pair<int, int>(to, weight)); //make new From map
		V.push_back(m_List+from);							 // insert m_List into vector
		beforeFrom = from;
	}
	else //when from is same
		m_List[from].insert(pair<int, int>(to, weight));
}

bool ListGraph::printGraph()
{
	ofstream fout;
	fout.open("log.txt", ios::app);
	if (m_Size < 0)
		return 0;

	fout << "======== PRINT========" << endl;

	for(int i=0; i<m_Size; i++)
	{
		fout << "[" << i << "]";

		for(auto it_=m_List[i].begin(); it_!=m_List[i].end() && fout<<" -> "; it_++)
		{
			fout << "(" << it_->first << "," << it_->second << ")";
		}
		fout << endl;
	}
	fout << "=====================" << endl
		 << endl;
	return 1;
}