#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "Graph.h"

class MatrixGraph : public Graph{
private:
	int** m_Mat;

public:
	MatrixGraph(bool type, int size);
	virtual ~MatrixGraph();	
		
	void getAdjacentEdges(int vertex, map<int, int>* m);
	void insertEdge(int from, int to, int weight);
	bool printGraph();
};

#endif