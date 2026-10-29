#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

int main()
{
    int vertexCount, edgeCount;
    cout << "Enter the number of vertices and undirected edges: ";
    if (!(cin >> vertexCount >> edgeCount) || vertexCount <= 0 || edgeCount < 0)
    {
        cerr << "Invalid number of vertices or edges.\n";
        return 1;
    }

    vector<vector<pair<int, int>>> graph(vertexCount);
    cout << "Enter each edge as: vertex1 vertex2 non-negative-weight "
            "(vertices numbered 1 to "
         << vertexCount << "):\n";
    for (int i = 0; i < edgeCount; ++i)
    {
        int first, second, weight;
        if (!(cin >> first >> second >> weight))
        {
            cerr << "Invalid edge input.\n";
            return 1;
        }
        if (first < 1 || first > vertexCount || second < 1 ||
            second > vertexCount)
        {
            cerr << "Edge vertices must be between 1 and " << vertexCount << ".\n";
            return 1;
        }
        if (weight < 0)
        {
            cerr << "Dijkstra's algorithm requires non-negative edge weights.\n";
            return 1;
        }

        --first;
        --second;
        graph[first].push_back({second, weight});
        graph[second].push_back({first, weight});
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
    priority_queue<pair<long long, int>,
                   vector<pair<long long, int>>,
                   greater<pair<long long, int>>> pending;
    distance[source - 1] = 0;
    pending.push({0, source - 1});

    while (!pending.empty())
    {
        long long currentDistance = pending.top().first;
        int vertex = pending.top().second;
        pending.pop();

        if (currentDistance != distance[vertex])
            continue;

        for (const auto &edge : graph[vertex])
        {
            long long newDistance = currentDistance + edge.second;
            if (newDistance < distance[edge.first])
            {
                distance[edge.first] = newDistance;
                pending.push({newDistance, edge.first});
            }
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
