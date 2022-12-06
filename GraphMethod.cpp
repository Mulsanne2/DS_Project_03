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

bool Kruskal(Graph* graph)
{
    graph->printGraph();
    int SIZE = graph->getSize();
    map<int, int> *MAP = new map<int, int>;
    map<int, int>::iterator iter;

    // int **VERTEX = new int *[SIZE];
    // for (int i = 0; i < SIZE; i++)
    // {
    //     VERTEX[i] = new int[SIZE];
    //     memset(VERTEX[i], 0, sizeof(int) * SIZE);
    // }
    int VERTEX[SIZE][SIZE];
    //initial all the array into 0
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            VERTEX[i][j] = 0;
        }
    }

    //load the all the graph index
    for (int i = 0; i < SIZE;i++){
        MAP->clear();
        graph->getAdjacentEdges(i, MAP);
        for (iter = MAP->begin(); iter != MAP->end();iter++){
            VERTEX[i][iter->first] = iter->second;
        }
    }

    vector<pair<int, pair<int, int>>> *LIST = new vector<pair<int, pair<int, int>>>;
    pair<int, pair<int, int>> TEMP;
    int NUM = 0;
    //put all the endges into vector to sort
    for (int i = 1; i < SIZE; i++)
    {
        for (int j = 0; j < i;j++){
            if(VERTEX[i][j]!=0){
                TEMP = make_pair(VERTEX[i][j], make_pair(i, j));
                LIST->push_back(TEMP); //put edges information into vector
                NUM++; //count edge of graph
            }
        }
    }
    InsertionSort(LIST, 0, 9);

    // delete[] VERTEX;
    return true;
}

// bool Dijkstra(Graph* graph, int vertex)
// {

// }

// bool Bellmanford(Graph* graph, int s_vertex, int e_vertex)
// {

// }

// bool FLOYD(Graph* graph)
// {

// }

void InsertionSort(vector<pair<int, pair<int, int>>> *LIST, int start, int end)
{   
    int j;
    pair<int, pair<int, int>> TEMP;
    for (int i = start+1; i <= end; i++){
        TEMP = LIST->at(i); //set first vertex

        for (j = i - 1; j >= start;j--){ //check vertex from the behind
            if(LIST->at(j).first > TEMP.first)
                LIST->at(j + 1) = LIST->at(j);
            else
                break;
        }
        LIST->at(j+1) = TEMP;
    }
}