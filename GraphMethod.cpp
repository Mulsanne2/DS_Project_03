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
    if(count!=1){
        delete MAP;
        delete[] Parent;
        delete LIST;
        fout.close();
        return false;
    }

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
    if(graph->getSize()<=vertex) //check if vertex number is bigger than graph return false
        return false;

    ofstream fout;
    fout.open("log.txt", ios::app);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; //declare priority queue

    int SIZE = graph->getSize(); //get the size of graph
    vector<bool> VISITED(SIZE, false); //initialize VISITED
    vector<int> DISTANCE(SIZE, MAX); //intitialize DISTANCE
    vector<int> PATH(SIZE, 0); //initialize PATH
    pq.push(make_pair(0,vertex));
    DISTANCE[vertex] = 0;
    VISITED[vertex] = true;
    map<int, int> *Adjacent = new map<int, int>;

    while(!pq.empty())
    {
        int curVertex = pq.top().second;
        int curWeight = pq.top().first;
        pq.pop();

        if (curWeight < 0){ // dijkstra algorithm can't have negative weight
            fout.close();
            return false;
        }

        VISITED[curVertex] = true;

        graph->getAdjacentEdges(curVertex, Adjacent); //get adjacent edges from current vertex
        auto iter = Adjacent->begin();
        while (iter != Adjacent->end())
        {
            int ToV = iter->first;
            int Weight = iter->second;

            if(DISTANCE[curVertex]+Weight<DISTANCE[ToV]){ //if it has shorter distance
                DISTANCE[ToV] = DISTANCE[curVertex] + Weight;
                PATH[ToV] = curVertex;
                pq.push(make_pair(DISTANCE[ToV], ToV));
            }

            iter++;
        }
    }

    cout << "====== Dijkstra =======" << endl;
    fout << "====== Dijkstra =======" << endl;
    cout << "startvertex: " << vertex << endl;
    fout << "startvertex: " << vertex << endl;
    for (int i = 0; i < SIZE;i++){
        if(i==vertex) //check if vertex is startpoint
            continue;

        cout << "[" << i << "] ";
        fout << "[" << i << "] ";
        if(VISITED[i]==false){ //check it's vertex isn't visited
            cout << "x" << endl;
            fout << "x" << endl;
        }
        else{
            int temp = i;
            stack<int> STACK;
            while (temp != vertex) //push vertex in stack until start vertex
            {
                STACK.push(temp);
                temp = PATH[temp];
            }
            cout << vertex;
            fout << vertex;

            while(!STACK.empty()){
                int pVertex = STACK.top();
                STACK.pop();
                cout << " -> " << pVertex;
                fout << " -> " << pVertex;
            }
            cout << " (" << DISTANCE[i] << ") " << endl;
            fout << " (" << DISTANCE[i] << ") " << endl;
        }
    }
    cout << "=====================" << endl
         << endl;
    fout << "=====================" << endl
         << endl;

    fout.close();
    delete Adjacent;
    return true;
}

bool Bellmanford(Graph* graph, int s_vertex, int e_vertex)
{
    if (graph->getSize() <= s_vertex || graph->getSize() <= e_vertex) //check if s_vertex and e_vertex is correct
        return false;
    else if(s_vertex==e_vertex) // check if start vertex and end vertex is same
        return false;

    ofstream fout;
    fout.open("log.txt", ios::app);
    int SIZE = graph->getSize();
    vector<int> DISTANCE(SIZE, MAX); //intitialize DISTANCE
    vector<int> PATH(SIZE, -1); //initialize PATH
    DISTANCE[s_vertex] = 0;

    map<int, int> *Adjacent = new map<int, int>;
    graph->getAdjacentEdges(s_vertex, Adjacent);

    auto iter = Adjacent->begin();
    while (iter != Adjacent->end()) //initialize distance and path from start vertex
    {
        int ToV = iter->first;
        int Weight = iter->second;
        DISTANCE[ToV] = Weight;
        PATH[ToV] = s_vertex;
        iter++;
    }

    vector<pair<pair<int, int>, int>> EDGES;
    for (int i = 0; i < SIZE; i++) //get all the edges
    {
        Adjacent->clear();
        graph->getAdjacentEdges(i, Adjacent);
        iter = Adjacent->begin();
        while (iter != Adjacent->end()) //insert all the edges in vector in (i) vertex
        {
            int tovertex = iter->first;
            int Weight = iter->second;
            if(tovertex==s_vertex){ //check if destination vertex is start vertex
                iter++;
                continue;
            }
            EDGES.push_back(make_pair(make_pair(i, tovertex), Weight));
            iter++;
        }
    }

    for (int k = 1; k < SIZE-1;k++){ //repeat n-2 times
        vector<pair<pair<int, int>, int>>::iterator iter2;
        for (iter2 = EDGES.begin(); iter2 != EDGES.end(); iter2++)
        {
            int fromvertex = iter2->first.first;
            int tovertex = iter2->first.second;
            int Length = iter2->second;

            if(DISTANCE[fromvertex]+Length<DISTANCE[tovertex]){ //if new path is shorter than previous path
                DISTANCE[tovertex] = DISTANCE[fromvertex] + Length;
                PATH[tovertex] = fromvertex;
            }
        }
    }
    vector<int> DISTANCE2(DISTANCE); //declare DISTANCE2 to store distance until n-1
    vector<pair<pair<int, int>, int>>::iterator iter2;
    for (iter2 = EDGES.begin(); iter2 != EDGES.end(); iter2++) //repeat one more time to find negative cycle exists
    {
        int fromvertex = iter2->first.first;
        int tovertex = iter2->first.second;
        int Length = iter2->second;

        if (DISTANCE[fromvertex] + Length < DISTANCE[tovertex]) // if new path is shorter than previous path
        {
            DISTANCE[tovertex] = DISTANCE[fromvertex] + Length;
            PATH[tovertex] = fromvertex;
        }
    }
    if(DISTANCE!=DISTANCE2) //check if graph has negative cycle
        return false;

    cout << "====== Bellman-Ford =======" << endl;
    fout << "====== Bellman-Ford =======" << endl;

    if(DISTANCE[e_vertex]==MAX){ //if two vertex isn't connected
        cout << "x" << endl;
        fout << "x" << endl;
    }
    else{ //if two vertex is connected
        int temp = e_vertex;
        stack<int> STACK;
        while (temp != s_vertex) // push vertex in stack until start vertex
        {
            STACK.push(temp);
            temp = PATH[temp];
        }
        cout << s_vertex;
        fout << s_vertex;
        while (!STACK.empty()) //print in reverse
        {
            int pVertex = STACK.top();
            STACK.pop();
            cout << " -> " << pVertex;
            fout << " -> " << pVertex;
        }
        cout << endl;
        fout << endl;
        cout << "cost: " << DISTANCE[e_vertex] << endl;
        fout << "cost: " << DISTANCE[e_vertex] << endl;
    }
    cout << "=====================" << endl
         << endl;
    fout << "=====================" << endl
         << endl;

    fout.close();
    delete Adjacent;
    return true;
}

bool FLOYD(Graph* graph)
{
    //get all the edges from graph and make matrix
    ofstream fout;
    fout.open("log.txt", ios::app);
    int SIZE = graph->getSize();
    vector<vector<int>> V(SIZE,vector<int>(SIZE, MAX));

    map<int, int> *Adjacent = new map<int, int>;
    map<int, int>::iterator iter;
    // vector<pair<pair<int, int>, int>> EDGES;
    for (int i = 0; i < SIZE;i++)
    {
        V[i][i] = 0;
    }
    for (int i = 0; i < SIZE; i++) // get all the edges
    {
        Adjacent->clear();
        graph->getAdjacentEdges(i, Adjacent);
        iter = Adjacent->begin();
        while (iter != Adjacent->end()) // insert all the edges in vector in (i) vertex
        {
            int tovertex = iter->first;
            int Weight = iter->second;
            V[i][tovertex] = Weight;
            // EDGES.push_back(make_pair(make_pair(i, tovertex), Weight));
            iter++;
        }
    }
    for (int k = 0; k < SIZE; k++)
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
                V[i][j] = min(V[i][j], V[i][k] + V[k][j]);
        }
    }

    //check if vertex has negative cycle
    for (int i = 0; i < SIZE; i++)
    {
        if(V[i][i]==-1)
            return false; //return false
    }

    cout << "======== FLOYD =========" << endl;
    fout << "======== FLOYD =========" << endl;
    cout << "\t";
    fout << "\t";
    for (int i = 0; i < SIZE;i++){
        cout << "[" << i << "]";
        fout << "[" << i << "]";
    }
    cout << endl;
    fout << endl;
    for (int i = 0; i < SIZE;i++){
        cout << "[" << i << "]\t";
        fout << "[" << i << "]\t";
        for (int j = 0; j < SIZE; j++){
            if (V[i][j]==MAX){
                cout << "x\t";
                fout << "x\t";
            }
            else{
                cout << V[i][j] << "\t";
                fout << V[i][j] << "\t";
            }
        }
        cout << endl;
        fout << endl;
    }
    cout << "=====================" << endl
         << endl;
    fout << "=====================" << endl
         << endl;

    fout.close();
    delete Adjacent;
    return true;
}

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
        if(end-start+1<=6){ //if size is less than 6, use quick sort
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