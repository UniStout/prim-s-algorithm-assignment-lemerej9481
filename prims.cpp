#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

// Prim's Algorithm using adjacency matrix
void primsAlgorithm(vector<vector<int>> &graph, int V)
{
    vector<int> parent(V, -1);   // Stores the MST
    vector<int> key(V, INT_MAX); // Min weight edge to include vertex
    vector<bool> inMST(V, false);

    // Start from vertex 0
    key[0] = 0;

    int totalWeight = 0;

    for (int count = 0; count < V - 1; count++)
    {
        // Pick the minimum key vertex not yet in MST
        int u = -1;
        for (int v = 0; v < V; v++)
        {
            if (!inMST[v] && (u == -1 || key[v] < key[u]))
                u = v;
        }

        if (u == -1 || key[u] == INT_MAX)
        {
            cout << "Graph is not connected." << endl;
            return;
        }

        inMST[u] = true;

        // Update key values of adjacent vertices
        for (int v = 0; v < V; v++)
        {
            if (graph[u][v] != 0 && !inMST[v] && graph[u][v] < key[v])
            {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    // Print MST
    cout << "Edge \tWeight" << endl;
    for (int i = 1; i < V; i++)
    {
        cout << parent[i] << " - " << i << "\t" << graph[parent[i]][i] << endl;
        totalWeight += graph[parent[i]][i];
    }
    cout << "Total MST Weight: " << totalWeight << endl;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream inFile(argv[1]);
    if (!inFile)
    {
        cerr << "Error: Could not open file '" << argv[1] << "'" << endl;
        return 1;
    }

    int V, E;
    inFile >> V >> E;

    // Initialize adjacency matrix with 0s
    vector<vector<int>> graph(V, vector<int>(V, 0));

    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        inFile >> u >> v >> w;
        graph[u][v] = w;
        graph[v][u] = w; // Undirected graph
    }

    inFile.close();

    cout << "Minimum Spanning Tree (Prim's Algorithm):" << endl;
    primsAlgorithm(graph, V);

    return 0;
}
// All procedures including main
