#include <iostream>
#include <limits>
#include <vector>
using namespace std;

struct Edge
{
    int from;
    int to;
    int weight;
};

int main()
{
    int vertexCount, edgeCount;
    cout << "Enter the number of vertices and directed edges: ";
    if (!(cin >> vertexCount >> edgeCount) || vertexCount <= 0 || edgeCount < 0)
    {
        cerr << "Invalid number of vertices or edges.\n";
        return 1;
    }

    vector<Edge> edges;
    edges.reserve(edgeCount);
    cout << "Enter each edge as: from to weight (vertices numbered 1 to "
         << vertexCount << "):\n";
    for (int i = 0; i < edgeCount; ++i)
    {
        int from, to, weight;
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

    int source;
    cout << "Enter the source vertex: ";
    if (!(cin >> source) || source < 1 || source > vertexCount)
    {
        cerr << "Source vertex must be between 1 and " << vertexCount << ".\n";
        return 1;
    }

    const long long infinity = numeric_limits<long long>::max();
    vector<long long> distance(vertexCount, infinity);
    distance[source - 1] = 0;

    for (int i = 1; i < vertexCount; ++i)
    {
        bool updated = false;
        for (const Edge &edge : edges)
        {
            if (distance[edge.from] != infinity &&
                distance[edge.from] + edge.weight < distance[edge.to])
            {
                distance[edge.to] = distance[edge.from] + edge.weight;
                updated = true;
            }
        }
        if (!updated)
            break;
    }

    for (const Edge &edge : edges)
    {
        if (distance[edge.from] != infinity &&
            distance[edge.from] + edge.weight < distance[edge.to])
        {
            cout << "A reachable negative-weight cycle exists. "
                    "Shortest distances are undefined.\n";
            return 0;
        }
    }

    cout << "\nShortest distances from vertex " << source << ":\n";
    for (int vertex = 0; vertex < vertexCount; ++vertex)
    {
        cout << "To vertex " << vertex + 1 << ": ";
        if (distance[vertex] == infinity)
            cout << "unreachable\n";
        else
            cout << distance[vertex] << '\n';
    }

    return 0;
}
