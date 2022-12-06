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
	auto iter = V.begin();

	if(from!=beforeFrom){ //when from is diffrent
		iter = V.insert(iter + from, m_List+from); //insert m_List into vector
		m_List[from].insert(pair<int, int>(to, weight)); //make new From map
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

	cout << "======== PRINT========" << endl;
	fout << "======== PRINT========" << endl;

	for(int i=0; i<m_Size; i++)
	{
		cout<<"["<<i<<"]";
		fout << "[" << i << "]";

		for(auto it_=m_List[i].begin(); it_!=m_List[i].end() && cout<<" -> "&&fout<<" -> "; it_++)
		{
			cout<<"("<<it_->first<<","<<it_->second<<")";
			fout << "(" << it_->first << "," << it_->second << ")";
		}
		cout<<endl;
		fout << endl;
	}
	cout << "=====================" << endl
		 << endl;
	fout << "=====================" << endl
		 << endl;
	return 1;
}