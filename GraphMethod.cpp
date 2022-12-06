#include "GraphMethod.h"

bool BFS(Graph* graph, int vertex)
{
    ofstream fout;
    fout.open("log.txt", ios::app);
    map<int, int> *Ad = new map<int, int>; // get adjacent List
    int Size = graph->getSize();
    bool *visited = new bool[Size];       // allocate visited
    fill(visited, visited + Size, false); // initialize all the visit into false

    if (vertex >= graph->getSize())
        return false;

    queue<int> Q; // instance stack
    Q.push(vertex);

    // print BFS
    fout << "======== BFS ========" << endl;
    cout << "======== BFS ========" << endl;
    fout << "startvertex: " << vertex << endl;
    cout << "startvertex: " << vertex << endl;
    fout << vertex;
    cout << vertex;

    visited[vertex] = true;

    while(!Q.empty()){
        vertex = Q.front();
        Q.pop();
        graph->getAdjacentEdges(vertex, Ad); // get adjacentEdge from CurNode

        for (map<int, int>::iterator iter = Ad->begin(); iter != Ad->end(); iter++) // get adjacent vertex
        {
            if (visited[iter->first] == false)
            {
                cout << " -> " << iter->first;
                fout << " -> " << iter->first;
                Q.push(iter->first); //push every vertex into queue
                visited[iter->first] = true;
            }
        }
    }
    cout << "\n=====================" << endl
         << endl;
    fout << "\n=====================" << endl
         << endl;
    delete Ad; //delete map
    delete[] visited; //delete bool array
    fout.close(); //close fout
    return true; //return
}

bool DFS(Graph* graph, int vertex)
{
    ofstream fout;
    fout.open("log.txt", ios::app);
    map<int, int> *Ad = new map<int, int>; // get adjacent List
    int Size = graph->getSize();
    bool *visited = new bool[Size]; // allocate visited
    fill(visited, visited + Size, false); // initialize all the visit into false

    if(vertex>=graph->getSize())
        return false;

    stack<int> S; // instance stack
    S.push(vertex);
    visited[vertex] = true;

    //print DFS
    fout << "======== DFS ========" << endl;
    cout << "======== DFS ========" << endl;
    fout << "startvertex: " << vertex << endl;
    cout << "startvertex: " << vertex << endl;
    fout << vertex;
    cout << vertex;

    while (!S.empty())
    {
        Ad->clear();
        int CurNode = S.top();
        graph->getAdjacentEdges(CurNode, Ad); // get adjacentEdge from CurNode
        S.pop();

        for (map<int, int>::iterator iter = Ad->begin(); iter != Ad->end(); iter++)
        {
            if (visited[iter->first] == false)
            {
                cout << " -> " << iter->first;
                fout << " -> " << iter->first;
                visited[iter->first] = true;
                S.push(CurNode);     // push back the CurNode before new Vertex
                S.push(iter->first); // push New Vertex into stack
                break;
            }
        }
    }
    cout << "\n=====================" << endl
         << endl;
    fout << "\n=====================" << endl
         << endl;
    delete Ad;
    delete[] visited;
    fout.close();
    return true;
}

bool DFS_R(Graph* graph, vector<bool>* visit, int vertex)
{
    ofstream fout;
    fout.open("log.txt", ios::app);
    auto iter = visit->at(vertex);
    iter = true;
    bool temp;
    cout << vertex;
    fout << vertex;
    map<int, int> *Ad = new map<int, int>;
    graph->getAdjacentEdges(vertex, Ad); //get the adjacent edge of vertex
    for (map<int, int>::iterator iter2 = Ad->begin(); iter2 != Ad->end(); iter2++){
        temp = visit->at(iter2->first);
        if(!temp){
            cout << " -> ";
            fout << " -> ";
            DFS_R(graph, visit, iter2->first); // call DFS_R recursive
        }
    }

    delete Ad;
    fout.close();
    return true;
}

// bool Kruskal(Graph* graph)
// {

// }

// bool Dijkstra(Graph* graph, int vertex)
// {

// }

// bool Bellmanford(Graph* graph, int s_vertex, int e_vertex)
// {

// }

// bool FLOYD(Graph* graph)
// {

// }