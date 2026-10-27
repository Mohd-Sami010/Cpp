#include <iostream>
#include <functional>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

struct SelectedEdge
{
    int from;
    int to;
    long long weight;
};

int main()
{
    int vertexCount, edgeCount;
    cout << "Enter the number of vertices and edges: ";
    if (!(cin >> vertexCount >> edgeCount) || vertexCount <= 0 || edgeCount < 0)
    {
        cerr << "Invalid number of vertices or edges.\n";
        return 1;
    }

    vector<vector<pair<int, long long>>> graph(vertexCount);
    cout << "Enter each edge as: vertex1 vertex2 weight (vertices numbered 1 to "
         << vertexCount << "):\n";

    for (int i = 0; i < edgeCount; ++i)
    {
        int from, to;
        long long weight;
        if (!(cin >> from >> to >> weight))
        {
            cerr << "Invalid edge input.\n";
            return 1;
        }
        if (from < 1 || from > vertexCount || to < 1 || to > vertexCount)
        {
            cerr << "Edge vertices must be between 1 and " << vertexCount << ".\n";
            return 1;
        }

        --from;
        --to;
        graph[from].push_back({to, weight});
        graph[to].push_back({from, weight});
    }

    priority_queue<tuple<long long, int, int>,
                   vector<tuple<long long, int, int>>,
                   greater<tuple<long long, int, int>>> edges;
    vector<bool> visited(vertexCount, false);
    vector<SelectedEdge> mst;
    long long totalWeight = 0;

    edges.push({0, 0, -1});
    while (!edges.empty() && mst.size() < static_cast<size_t>(vertexCount))
    {
        long long weight;
        int vertex, parent;
        tie(weight, vertex, parent) = edges.top();
        edges.pop();

        if (visited[vertex])
            continue;

        visited[vertex] = true;
        if (parent != -1)
        {
            mst.push_back({parent, vertex, weight});
            totalWeight += weight;
        }

        for (const auto &edge : graph[vertex])
        {
            if (!visited[edge.first])
                edges.push({edge.second, edge.first, vertex});
        }
    }

    if (mst.size() != static_cast<size_t>(vertexCount - 1))
    {
        cerr << "The graph is disconnected; a spanning tree does not exist.\n";
        return 1;
    }

    cout << "\nEdges in the Minimum Spanning Tree:\n";
    for (const SelectedEdge &edge : mst)
        cout << edge.from + 1 << " - " << edge.to + 1
             << " (weight: " << edge.weight << ")\n";
    cout << "Total weight of the MST: " << totalWeight << '\n';

    return 0;
}