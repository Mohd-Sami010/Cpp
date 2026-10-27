#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

struct Edge
{
    int from;
    int to;
    long long weight;
};

class DisjointSet
{
private:
    vector<int> parent;
    vector<int> rank;

public:
    explicit DisjointSet(int size) : parent(size), rank(size, 0)
    {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int vertex)
    {
        if (parent[vertex] != vertex)
            parent[vertex] = find(parent[vertex]);
        return parent[vertex];
    }

    bool unite(int first, int second)
    {
        int firstRoot = find(first);
        int secondRoot = find(second);
        if (firstRoot == secondRoot)
            return false;

        if (rank[firstRoot] < rank[secondRoot])
            swap(firstRoot, secondRoot);
        parent[secondRoot] = firstRoot;
        if (rank[firstRoot] == rank[secondRoot])
            ++rank[firstRoot];
        return true;
    }
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

    vector<Edge> edges;
    edges.reserve(edgeCount);
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

        edges.push_back({from - 1, to - 1, weight});
    }

    sort(edges.begin(), edges.end(), [](const Edge &first, const Edge &second)
         { return first.weight < second.weight; });

    DisjointSet sets(vertexCount);
    vector<Edge> mst;
    long long totalWeight = 0;

    for (const Edge &edge : edges)
    {
        if (sets.unite(edge.from, edge.to))
        {
            mst.push_back(edge);
            totalWeight += edge.weight;
            if (mst.size() == static_cast<size_t>(vertexCount - 1))
                break;
        }
    }

    if (mst.size() != static_cast<size_t>(vertexCount - 1))
    {
        cerr << "The graph is disconnected; a spanning tree does not exist.\n";
        return 1;
    }

    cout << "\nEdges in the Minimum Spanning Tree:\n";
    for (const Edge &edge : mst)
        cout << edge.from + 1 << " - " << edge.to + 1
             << " (weight: " << edge.weight << ")\n";
    cout << "Total weight of the MST: " << totalWeight << '\n';

    return 0;
}
