#include "Manager.h"

Manager::Manager()
{
	graph = nullptr;
	fout.open("log.txt", ios::app);
	load = 0;
}

Manager::~Manager()
{
	if(load)
		// delete graph;
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
	
	char* str=NULL;
	char* str2=NULL;
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
			if (!mKRUSKAL())
				printErrorCode(500);
		}
	}	
	fin.close();
}

bool Manager::LOAD(char* filename)
{
	char buf[129] = {0};
	string buf2;
	bool graphType = 0;
	if(graph) //check if graph already exists
		return false;

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
	BFS(graph2, vertex);
	return true;
}

bool Manager::mDFS(int vertex)
{	
	if(!graph)
		return false;
	else if(vertex<0)
		return false;
	DFS(graph2, vertex);
	return true;
}


bool Manager::mDFS_R(int vertex)
{
	if (!graph)
		return false;
	else if (vertex < 0)
		return false;

	vector<bool> *visited=new vector<bool>;
	for (int i = 0; i < graph->getSize();i++)
		visited->push_back(false);

	// print DFS_R
	fout << "======== DFS_R ========" << endl;
	cout << "======== DFS_R ========" << endl;
	fout << "startvertex: " << vertex << endl;
	cout << "startvertex: " << vertex << endl;
	DFS_R(graph2, visited, vertex);
	cout << "\n=====================" << endl
		 << endl;
	fout << "\n=====================" << endl
		 << endl;
	return true;
}

// bool Manager::mDIJKSTRA(int vertex)
// {

// }

bool Manager::mKRUSKAL()
{
	//check if graph exist
	if(!graph)
		return false;

	Kruskal(graph2);
	return true;
}

// bool Manager::mBELLMANFORD(int s_vertex, int e_vertex)
// {

// }

// bool Manager::mFLOYD()
// {

// }

void Manager::printErrorCode(int n)
{ // ERROR CODE PRINT
	fout<<"======== ERROR ========"<<endl;
	fout<<n<<endl;
	fout << "=======================" << endl
		 << endl;

	cout << "======== ERROR ========" << endl;
	cout << n << endl;
	cout << "=======================" << endl
		 << endl;
}

void Manager::printSuccessCode(string str)
{ // SUCCESS CODE PRINT

	fout << "=========" << str << "=========" << endl;
	fout << "SUCCESS" << endl;
	fout << "=======================" << endl
		 << endl;

	cout << "=========" << str << "=========" << endl;
	cout << "SUCCESS" << endl;
	cout << "=======================" << endl
		 << endl;
}
