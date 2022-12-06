#ifndef _GRAPHMETHOD_H_
#define _GRAPHMETHOD_H_

#include "ListGraph.h"
#include "MatrixGraph.h"
// #include "vertexSet.h"

bool BFS(Graph* graph, int vertex);
bool DFS(Graph* graph, int vertex);
bool DFS_R(Graph *graph, vector<bool> *visit, int vertex, ofstream *fout);
bool Kruskal(Graph* graph);
bool Dijkstra(Graph* graph, int vertex);
bool Bellmanford(Graph* graph, int s_vertex, int e_vertex);
bool FLOYD(Graph* graph);

void InsertionSort(vector<pair<int, pair<int, int>>> *LIST, int start, int end); //insertion sort
void QuickSort(vector<pair<int, pair<int, int>>> *LIST, int start, int end); //quick sort

int FIND(int *arr, int num);
void UNION(int *arr, int v1, int v2);
#endif
