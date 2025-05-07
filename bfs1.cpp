#include <iostream>
#include <omp.h>
#include <chrono>
#include <vector>
#include <queue>

using namespace std;

class Graph
{
public:
    int vertices, edges;
    vector<vector<int>> graph;
    vector<bool> visited;

    Graph(int v, int u) : vertices(v), edges(u)
    {
        graph.resize(vertices);
    }

    void addEdge(int u, int v)
    {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    void initialize_visited()
    {
        visited.assign(vertices, false);
    }

    void bfs(int start)
    {
        queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty())
        {
            int curr = q.front();
            q.pop();

            cout << curr << " ";

            for (int neig : graph[curr])
            {
                if (!visited[neig])
                {
                    visited[neig] = true;
                    q.push(neig);
                }
            }
        }
    }
    void bfsParallel(int start)
    {
        queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty())
        {
            int curr = q.front();
            q.pop();

            cout << curr << " ";

#pragma omp parallel for
            for (int neig : graph[curr])
            {
                if (!visited[neig])
                {
#pragma omp critical
                    if (!visited[neig])
                    {
                        visited[neig] = true;
                        q.push(neig);
                    }
                }
            }
        }
    }

    void printGraph()
    {
        for (int i = 0; i < vertices; i++)
        {
            cout << i << " -> ";
            for (int j : graph[i])
            {
                cout << j << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    int v, e;

    cout << "\nEnter the number of vertices : ";
    cin >> v;
    cout << "\nEnter the number of edges : ";
    cin >> e;

    Graph g(v, e);

    cout << "\nEnter the edges (u v) : \n";
    for (int i = 0; i < e; i++)
    {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    cout << "\nGraph Representation : \n";
    g.printGraph();

    g.initialize_visited();

    cout << "\nSerial BFS start from node 0: ";
    auto start = chrono::high_resolution_clock::now();
    g.bfs(0);
    auto end = chrono::high_resolution_clock::now();
    cout << endl;

    cout << "\nTime taken by Serial BFS : " << chrono ::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;

    g.initialize_visited();

    cout << "\nParallel BFS start from node 0: ";
    start = chrono::high_resolution_clock::now();
    g.bfsParallel(0);
    end = chrono::high_resolution_clock::now();

    cout << "\nTime taken by Parallel BFS : " << chrono ::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;

    return 0;
}