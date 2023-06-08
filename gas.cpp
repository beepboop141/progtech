#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

const int INF = INT_MAX; // Infinity

struct Edge {
    int to;
    int length;
};

void addEdge(vector<vector<Edge>>& graph, int from, int to, int length) {
    graph[from].push_back({ to, length });
    graph[to].push_back({ from, length });
}

int getRefills(int w, vector<int>& path, vector<vector<Edge>>& graph) {
    int tank = 0;
    int refills = 0;
    for (int i = 0; i < path.size() - 1; i++) {
        int u = path[i];
        int v = path[i + 1];
        int weight = -1;
        for (const Edge& edge : graph[u]) {
            if (edge.to == v) {
                weight = edge.length;
                break;
            }
        }
        if (weight > tank) {
            tank = w;
            refills++;
        }
        tank -= weight;
    }
    return refills;
}

bool isPossible(vector<vector<Edge>>& graph, int A, int B, int C, vector<int>& route, int& fills) {
    int n = graph.size();
    vector<bool> visited(n, false);
    vector<int> dist(n, INF);
    vector<int> prev(n, -1);
    
    dist[A] = 0;
    visited[A] = true;
    
    queue<int> q;
    q.push(A);
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (const Edge& edge : graph[u]) {
            int v = edge.to;
            int weight = edge.length;
            
            if (!visited[v] && weight <= C) {
                visited[v] = true;
                dist[v] = dist[u] + 1;
                prev[v] = u;
                q.push(v);
                
                if (v == B) {
                    // Path from city A to city B found
                    int node = B;
                    while (node != -1) {
                        route.push_back(node);
                        node = prev[node];
                    }
                    reverse(route.begin(), route.end());
                    fills = getRefills(C, route, graph);
                    return true;
                }
            }
        }
    }
    
    return false;
}

int main() {
    int N, M;
    cin >> N >> M;
    
    vector<vector<Edge>> graph(N);
    
    for (int i = 0; i < M; i++) {
        int U, V, L;
        cin >> U >> V >> L;
        addEdge(graph, U, V, L);
    }
    
    int Q;
    cin >> Q;
    
    for (int i = 0; i < Q; i++) {
        int A, B, C;
        cin >> A >> B >> C;
        
        vector<int> route;
        int fills = 0;
        bool possible = isPossible(graph, A, B, C, route, fills);
        
        if (possible) cout << "POSSIBLE: " + to_string(fills) + " fill(s), " ; 
        else cout << "IMPOSSIBLE" << endl;
        if (possible) {
            for (int j = 0; j < route.size(); j++) {
                cout << route[j];
                if (j < route.size() - 1) {
                    cout << " ";
                }
            }
            cout << endl;
        }
    }
    
    return 0;
}
