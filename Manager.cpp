#include "Manager.h"

Manager::Manager()
{
	graph = nullptr;
	graph2 = nullptr;
	fout.open("log.txt", ios::app);
	load = 0;
}

Manager::~Manager()
{
	if(load){
		delete graph;
		delete graph2;
	}
	fout.close();
}

void Manager::run(const char* command_txt){
	ifstream fin;
	fin.open(command_txt);
		
	if(!fin)
	{
		fout<<"[ERROR] command file open error!"<<endl;
		return;
	}

	char *str = NULL;
	char *str2 = NULL;
	char *str3 = NULL;
	char buf[129]={0};

	while(fin.getline(buf, 128))
	{
		if (buf[0] == 0) // check if buffer is NULL
			continue;
		str = strtok(buf, " "); //cut string by space

		if (strcmp(str, "LOAD") == 0)
		{
			str2 = strtok(NULL, " ");
			if(LOAD(str2))
				printSuccessCode("LOAD");
		}

		else if(strcmp(str, "PRINT") == 0)
		{
			if(!PRINT())
				printErrorCode(200);
		}

		else if (strcmp(str, "BFS") == 0)
		{
			str2 = strtok(NULL, " ");
			if(str2==NULL)
			{ // check start vertex
				printErrorCode(300);
				continue;
			}
			int Startvertex = stoi(str2);
			if(!mBFS(Startvertex)) //mBFS
				printErrorCode(300);
		}

		else if (strcmp(str, "DFS") == 0)
		{
			str2 = strtok(NULL, " ");
			if(str2==NULL){ //check start vertex
				printErrorCode(400);
				continue;
			}
			int Startvertex = stoi(str2);
			if(!mDFS(Startvertex)) //mDFS
				printErrorCode(400);
		}

		else if (strcmp(str, "DFS_R") == 0)
		{
			str2 = strtok(NULL, " ");
			if (str2 == NULL) // check start vertex
			{
				printErrorCode(500);
				continue;
			}
			int Startvertex = stoi(str2);
			if (!mDFS_R(Startvertex)) //mDFS_R
				printErrorCode(500);
		}

		else if (strcmp(str, "KRUSKAL") == 0)
		{
			if (!mKRUSKAL()) //KRUSKAL
				printErrorCode(600);
		}

		else if (strcmp(str, "DIJKSTRA") == 0)
		{
			str2 = strtok(NULL, " ");
			if (str2 == NULL) // check start vertex
			{
				printErrorCode(700);
				continue;
			}
			int Startvertex = stoi(str2);
			if (!mDIJKSTRA(Startvertex)) //DIJKSTRA
				printErrorCode(700);
		}

		else if (strcmp(str, "BELLMANFORD") == 0)
		{
			str2 = strtok(NULL, " ");
			str3 = strtok(NULL, " ");
			if (str2 == NULL || str3 == NULL) // check start vertex
			{
				printErrorCode(800);
				continue;
			}
			int Startvertex = stoi(str2);
			int Endvertex = stoi(str3);
			if (!mBELLMANFORD(Startvertex, Endvertex)) // DIJKSTRA
				printErrorCode(800);
		}

		else if (strcmp(str, "FLOYD") == 0)
		{
			if (!mFLOYD()) // KRUSKAL
				printErrorCode(900);
		}

		else if (strcmp(str, "EXIT") == 0)
		{
			return; //exit run
		}
		
		else{
			fout << "Wrong Command" << endl
				 << endl;
		}
	}	
	fin.close();
}

bool Manager::LOAD(char* filename)
{
	char buf[129] = {0};
	string buf2;
	bool graphType = 0;
	
	if(load==1){ //if graph is already exist, then erase before graph
		delete graph;
		delete graph2;
	}
	ifstream openGraph;
	openGraph.open(filename);

	if(!openGraph) //if graph file doesn't open
	{
		fout << "[ERROR] graph file open error!" << endl;
		return false;
	}
	
	if(!openGraph.getline(buf,128)){ //read type of graph
		return false;
	}

	if(buf[0]=='L') //when graph type is List
		graphType = 0;
	else if (buf[0]=='M') //when graph type is Matrix
		graphType = 1;
	else
		return false;

	if (!openGraph.getline(buf, 128))
	{ // read size of graph
		return false;
	}

	int Size = stoi(buf); //get the size of graph
	if(Size<=0)
		return false;

	if (graphType == 0) //if graph type is List then construct List graph
		graph = new ListGraph(graphType, Size);
	else //if graph type is Matrix then construct Matrix graph
		graph = new MatrixGraph(graphType, Size);

	graph2 = new MatrixGraph(1, Size);
	load = 1; //set load into 1

	//insert graph is List
	if(graphType==0){
		int From = 0;
		while(openGraph.getline(buf,128)){
			int To = 0, Weight = 0;
			buf2 = buf;
			char *buf3 = NULL;

			if (buf2.find(' ') == -1 || buf2.find(' ') + 1 >= buf2.size()) //check if input is From point
			{
				From = stoi(buf);
				continue;
			}

			else{
				buf3 = strtok(buf, " "); //get To vertex
				To = stoi(buf3); //change type into int
				buf3 = strtok(NULL, " "); //get weight
				if(buf3==NULL) //check if weight is exist
					return false;
				Weight = stoi(buf3); //change type into int
			}

			graph->insertEdge(From, To, Weight); //insert direct graph
			graph2->insertEdge(From, To, Weight); // insert undirect graph
			graph2->insertEdge(To, From, Weight); // insert undirect graph
		}
	}

	//insert graph is Matrix
	else if(graphType==1){
		int From = 0;
		while (openGraph.getline(buf, 128))
		{
			int To = 0, Weight = 0;
			buf2 = buf;
			char *buf3 = NULL;

			buf3 = strtok(buf, " ");
			Weight = stoi(buf3);
			for (int i = 0; i < Size;i++){
				graph->insertEdge(From, i, Weight);//insert direct graph

				//make undiret graph
				if(Weight!=0){ //if weight is not 0 then put into undirect graph
					graph2->insertEdge(From, i, Weight); //insert undirect graph
					graph2->insertEdge(i, From, Weight); //insert undirect graph
				}

				buf3 = strtok(NULL, " "); //get the next weight
				if(buf3==NULL)
					break;
				Weight = stoi(buf3);
			}
			From++;
		}
	}

	openGraph.close();
	return true;
}

bool Manager::PRINT()
{
	if(!graph)
		return false;
	else if(graph->getSize()==0)
		return false;
	if(graph->printGraph())
		return true;
	return false;
}

bool Manager::mBFS(int vertex)
{
	if (!graph)
		return false;
	else if (vertex < 0)
		return false;
	if(BFS(graph2, vertex))
		return true;
	else
		return false;
}

bool Manager::mDFS(int vertex)
{	
	if(!graph)
		return false;
	else if(vertex<0)
		return false;
	if(DFS(graph2, vertex))
		return true;
	else
		return false;
}


bool Manager::mDFS_R(int vertex)
{
	if (!graph)
		return false;
	else if (vertex < 0)
		return false;
	else if (graph->getSize() <= vertex)
		return false;

	vector<bool> *visited=new vector<bool>;
	for (int i = 0; i < graph->getSize();i++)
		visited->push_back(false);

	// print DFS_R
	fout << "======== DFS_R ========" << endl;
	fout << "startvertex: " << vertex << endl;
	DFS_R(graph2, visited, vertex, &fout);
	fout << "\n=====================" << endl
		 << endl;
	
	delete visited;
	return true;
}

bool Manager::mDIJKSTRA(int vertex)
{
	if (!graph) //check if graph exist
		return false;
	else if(vertex <0) //check vertex is available
		return false;

	if(Dijkstra(graph, vertex)) //Dijkstra
		return true;
	return false;
}

bool Manager::mKRUSKAL()
{
	//check if graph exist
	if(!graph2)
		return false;

	if(Kruskal(graph2)) //Kruskal
		return true;
	else
		return false;
}

bool Manager::mBELLMANFORD(int s_vertex, int e_vertex)
{

	if (!graph) // check if graph exist
		return false;
	else if (s_vertex < 0 || e_vertex < 0) // check vertex is available
		return false;

	if (Bellmanford(graph, s_vertex, e_vertex)) //Bellmanford
		return true;
	return false;
}

bool Manager::mFLOYD()
{
	if (!graph) // check if graph exist
		return false;

	if(FLOYD(graph)) //FLOYD function
		return true;
	else
		return false;
}

void Manager::printErrorCode(int n)
{ // ERROR CODE PRINT
	fout<<"======== ERROR ========"<<endl;
	fout<<n<<endl;
	fout << "=======================" << endl
		 << endl;
}

void Manager::printSuccessCode(string str)
{ // SUCCESS CODE PRINT

	fout << "=========" << str << "=========" << endl;
	fout << "SUCCESS" << endl;
	fout << "=======================" << endl
		 << endl;
}
