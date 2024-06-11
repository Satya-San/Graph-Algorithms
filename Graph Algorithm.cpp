#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

class Graph {
private:
    int V;
    vector<vector<pair<int, int>>> adj;

    void DFSUtil(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";
        for (auto& i : adj[v]) {
            if (!visited[i.first]) {
                DFSUtil(i.first, visited);
            }
        }
    }

public:
    Graph(int V) : V(V), adj(V) {}

    void addEdge(int v, int w, int weight = 1) {
        adj[v].push_back(make_pair(w, weight));
        adj[w].push_back(make_pair(v, weight));  // Uncomment for undirected graph
    }

    void DFS(int v) {
        vector<bool> visited(V, false);
        DFSUtil(v, visited);
    }

    void BFS(int s) {
        vector<bool> visited(V, false);
        queue<int> q;
        visited[s] = true;
        q.push(s);

        while (!q.empty()) {
            s = q.front();
            cout << s << " ";
            q.pop();

            for (auto& i : adj[s]) {
                if (!visited[i.first]) {
                    visited[i.first] = true;
                    q.push(i.first);
                }
            }
        }
    }

    void Dijkstra(int src) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> dist(V, INT_MAX);

        pq.push(make_pair(0, src));
        dist[src] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (auto& x : adj[u]) {
                int v = x.first;
                int weight = x.second;

                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }

        cout << "Vertex Distance from Source\n";
        for (int i = 0; i < V; ++i)
            cout << i << "\t\t" << dist[i] << "\n";
    }

    void PrimMST() {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        int src = 0;
        vector<int> key(V, INT_MAX);
        vector<int> parent(V, -1);
        vector<bool> inMST(V, false);

        pq.push(make_pair(0, src));
        key[src] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            inMST[u] = true;

            for (auto& x : adj[u]) {
                int v = x.first;
                int weight = x.second;

                if (!inMST[v] && key[v] > weight) {
                    key[v] = weight;
                    pq.push(make_pair(key[v], v));
                    parent[v] = u;
                }
            }
        }

        for (int i = 1; i < V; ++i)
            cout << parent[i] << " - " << i << "\n";
    }
};

int main() {
    int V = 9;
    Graph g(V);

    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);

    cout << "Depth First Traversal (starting from vertex 2)\n";
    g.DFS(2);
    cout << "\n\n";

    cout << "Breadth First Traversal (starting from vertex 2)\n";
    g.BFS(2);
    cout << "\n\n";

    cout << "Shortest paths from vertex 0\n";
    g.Dijkstra(0);
    cout << "\n\n";

    cout << "Minimum Spanning Tree (Prim's Algorithm)\n";
    g.PrimMST();
    cout << "\n\n";

    return 0;
}
