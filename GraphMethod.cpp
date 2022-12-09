#include "GraphMethod.h"

bool BFS(Graph* graph, int vertex)
{
    if (graph->getSize() < vertex) // check if vertex number is bigger than graph return false
        return false;

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
    if (graph->getSize() < vertex) // check if vertex number is bigger than graph return false
        return false;

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

bool DFS_R(Graph *graph, vector<bool> *visit, int vertex, ofstream *fout)
{

    if (graph->getSize() < vertex) // check if vertex number is bigger than graph return false
        return false;

    auto iter = visit->at(vertex);
    iter = true;
    bool temp;
    cout << vertex;
    *fout << vertex;
    map<int, int> *Ad = new map<int, int>;
    graph->getAdjacentEdges(vertex, Ad); //get the adjacent edge of vertex
    for (map<int, int>::iterator iter2 = Ad->begin(); iter2 != Ad->end(); iter2++){
        temp = visit->at(iter2->first);
        if(!temp){
            cout << " -> ";
            *fout << " -> ";
            DFS_R(graph, visit, iter2->first, fout); // call DFS_R recursive
        }
    }

    delete Ad;
    return true;
}

bool Kruskal(Graph* graph)
{
    ofstream fout;
    fout.open("log.txt", ios::app);
    int SIZE = graph->getSize();
    map<int, int> *MAP = new map<int, int>;
    map<int, int>::iterator iter;

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
    //put all the endges into vector to sort
    for (int i = 1; i < SIZE; i++)
    {
        for (int j = 0; j < i;j++){
            if(VERTEX[i][j]!=0){
                TEMP = make_pair(VERTEX[i][j], make_pair(i, j));
                LIST->push_back(TEMP); //put edges information into vector
            }
        }
    }
    int NUM = LIST->size();
    
    //Sort the edges with Quick Sort
    QuickSort(LIST, 0, NUM-1);

    int VERTEX2[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            VERTEX2[i][j] = 0;
        }
    }
    
    pair<int, pair<int, int>> TEMP2;
    int LENGTH = 0; //LENGTH of KRUSKAL
    // initialize all the parents
    int *Parent = new int[SIZE];
    for (int i = 0; i < SIZE;i++)
        Parent[i] = -1;

    while(!LIST->empty()){
        TEMP2 = LIST->at(0);
        LIST->erase(LIST->begin());

        int V1 = TEMP2.second.first;
        int V2 = TEMP2.second.second;
        int parent1 = FIND(Parent, V1);
        int parent2 = FIND(Parent, V2);

        if(parent1==-1&&parent2==-1){ //if both vertex doesn't have parent
            UNION(Parent, V1, V2);
            LENGTH += TEMP2.first;
            VERTEX2[V1][V2] = TEMP2.first; //add on VERTEX2 array the result edge
            VERTEX2[V2][V1] = TEMP2.first; // add on VERTEX2 array the result edge
        }
        else if(parent1 ==V2||parent2==V1) //if parent is same
            continue;
        else if(parent1!=parent2){
            if(parent1==-1){
                UNION(Parent, parent2, V1);
                VERTEX2[V1][V2] = TEMP2.first; // add on VERTEX2 array the result edge
                VERTEX2[V2][V1] = TEMP2.first; // add on VERTEX2 array the result edge
            }
            else{
                UNION(Parent, parent1, V2);
                VERTEX2[V1][V2] = TEMP2.first; // add on VERTEX2 array the result edge
                VERTEX2[V2][V1] = TEMP2.first; // add on VERTEX2 array the result edge
            }
            LENGTH += TEMP2.first;
        }
    }

    //check if graph is connected
    int count = 0;
    for (int i = 0; i < SIZE;i++){
        if(Parent[i]==-1)
            count++;
    }

    //check if graph isn't connected
    if(count!=1)
        return false;

    //print the result
    cout << "====== Kruskal =======" << endl;
    fout << "====== Kruskal =======" << endl;
    for (int i = 0; i < SIZE; i++)
    {
        cout << "[" << i << "] ";
        fout << "[" << i << "] ";
        for (int j = 0; j < SIZE; j++){
            if(VERTEX2[i][j]!=0){
                cout << j << "(" << VERTEX2[i][j] << ") ";
                fout << j << "(" << VERTEX2[i][j] << ") ";
            }
        }
        cout << endl;
        fout << endl;
    }
    cout << "cost: " << LENGTH << endl;
    fout << "cost: " << LENGTH << endl;
    cout << "=====================" << endl
         << endl;
    fout << "=====================" << endl
         << endl;

    delete MAP;
    delete[] Parent;
    delete LIST;
    fout.close();
    return true;
}

bool Dijkstra(Graph* graph, int vertex)
{
    if(graph->getSize()<vertex) //check if vertex number is bigger than graph return false
        return false;

    int SIZE = graph->getSize(); //get the size of graph
    vector<bool> VISITED(SIZE, false);
    vector<int> DISTANCE(SIZE, MAX);
    vector<int> PATH(SIZE, 0);
    map<int, int> *Adjacent = new map<int, int>;
    graph->getAdjacentEdges(vertex, Adjacent);
    auto iter = Adjacent->begin();
    while(iter!=Adjacent->end()){
        int ToV = iter->first;
        int Weight = iter->second;
        iter++;
    }


    // Adjacent->erase(6);

    delete Adjacent;
    return true;
}

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
        LIST->at(j+1) = TEMP; //set TEMP
    }
}

void QuickSort(vector<pair<int, pair<int, int>>> *LIST, int start, int end)
{
    if(start<end){
        if(end-start+1<=6){
            InsertionSort(LIST, start, end);
        }
        else{
            pair<int, pair<int, int>> TEMP;
            //set pivot for first values
            int pivot = LIST->at(start).first;
            int i = start + 1;
            int j = end;

            while(i<j){
                while (LIST->at(i).first < pivot) //find larger data from front
                    i++;
                while (LIST->at(j).first > pivot) //find smaller data from last
                    j--;
                if(i<=j){
                    TEMP = LIST->at(i);
                    LIST->at(i) = LIST->at(j);
                    LIST->at(j) = TEMP;
                }
            }
            //move pivot into right position
            TEMP = LIST->at(start);
            LIST->at(start) = LIST->at(j);
            LIST->at(j) = TEMP;

            QuickSort(LIST, start, pivot - 1);
            QuickSort(LIST, pivot + 1, end);
        }

    }
}

int FIND(int *arr, int num)
{
    int inputnum = num;
    while(arr[num]>=0) //check if it has root
        num = arr[num];

    if(num==inputnum)
        return -1;
    return num;
}

void UNION(int *arr, int v1, int v2)
{
    arr[v1] = v2; //connect edge
}