#ifndef _LIST_H_
#define _LIST_H_

#include "Graph.h"

class ListGraph : public Graph{
private:
	map < int, int >* m_List;
	vector<map<int, int> *> V;
	int beforeFrom;

public:	
	ListGraph(bool type, int size);
	virtual ~ListGraph();
		
	void getAdjacentEdges(int vertex, map<int, int>* m);
	void insertEdge(int from, int to, int weight);
	bool printGraph();
};

#endif