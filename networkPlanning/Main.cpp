// C++ program for implementation of Ford Fulkerson algorithm
#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
using namespace std;

#define V 6

struct maxFlowNetwork{
	int source;
	int destination;
	bool possibleNetwork[V][V];
	int maximumFlow;
};

bool bfs(int rGraph[V][V], int s, int t, int parent[])
{
	
	bool visited[V];
	memset(visited, 0, sizeof(visited));


	queue <int> q;
	q.push(s);
	visited[s] = true;
	parent[s] = -1;

	while (!q.empty())
	{
		int u = q.front();
		q.pop();

		for (int v = 0; v<V; v++)
		{
			if (visited[v] == false && rGraph[u][v] > 0)
			{
				q.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}

	
	return (visited[t] == true);
}

void maxFlow(int graph[V][V], maxFlowNetwork* network)
{
	int u, v;
	int rGraph[V][V]; 
	for (u = 0; u < V; u++)
		for (v = 0; v < V; v++)
			rGraph[u][v] = graph[u][v];

	int parent[V]; 

	int max_flow = 0; 

					
	while (bfs(rGraph, network->source, network->destination, parent))
	{
		
		int path_flow = INT_MAX;
		for (v = network->destination; v != network->source; v = parent[v])
		{
			u = parent[v];
			path_flow = min(path_flow, rGraph[u][v]);
		}
		
		for (v = network->destination; v != network->source; v = parent[v])
		{
			u = parent[v];
			rGraph[u][v] -= path_flow;
			network->possibleNetwork[u][v] = true;
		}
		max_flow += path_flow;
	}
	network->maximumFlow = max_flow;
}

int main()
{
	int graph[V][V] = 
	{ 
		{ 0, 16, 13, 0, 0, 0 },
		{ 0, 0, 10, 12, 0, 0 },
		{ 0, 4, 0, 0, 14, 0 },
		{ 0, 0, 9, 0, 0, 20 },
		{ 0, 0, 0, 7, 0, 4 },
		{ 0, 0, 0, 0, 0, 0 }
	};

	maxFlowNetwork network;
	network.source = 0; //source
	network.destination = 5; //sink
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V;j++) {
			network.possibleNetwork[i][j] = 0;
		}
	}
	maxFlow(graph, &network);
	cout << "The maximum possible flow is " << network.maximumFlow << endl;
	cout << "Possible Network" << endl;
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V;j++) {
			cout << network.possibleNetwork[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}
