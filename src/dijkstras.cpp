#include "dijkstras.h"
#include <algorithm>


//constexpr int INF = numeric_limits<int>::max();

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
    int n = G.numVertices;
    vector<int> distance(n, INF); //infinity
    vector<bool> visited(n, false);
    
    previous.assign(n, -1);

    using Node = pair<int, int>; // (distance, vertex)
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    distance[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int curr = pq.top().second;
        pq.pop();

        if (visited[curr]) continue;
        visited[curr] = true;

        for (const Edge& neighbor : G[curr]) {
            int v = neighbor.dst;
            int weight = neighbor.weight;

            if (!visited[v] && distance[curr] + weight < distance[v]) {
                distance[v] = distance[curr] + weight;
                previous[v] = curr;
                pq.push({distance[v], v});
            }
        }
    }
    return distance;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination){
    vector<int> path;
    for (int i = destination; i != -1; i = previous[i]){
        path.push_back(i);
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total){
    // if (v.empty()){
    //     cout << "No path found." << endl;
    //     return;
    // }
    if (total == INF){
         cout << "No path found." << endl;
         return;
    }
    for (size_t i = 0; i < v.size(); ++i){
        cout << v[i] <<" ";
        
    }
    cout << "\nTotal cost is " << total << endl;
}