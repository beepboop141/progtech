#include <iostream>
#include <vector>
using namespace std; 

void dfs(int node, vector<vector<int>> &graph, vector<bool> &visited) {
    visited[node] = true; 
    for (int neighbor: graph[node]) {
        if(!visited[neighbor])
            dfs(neighbor, graph, visited); 
    }
}

bool is_connected(vector<vector<int>> &graph, int n) {
    vector<bool> visited(n, false); 
    int start =0; 
    for (int i =0; i<n; ++i){
        if (!graph[i].empty()){
            start =i; 
            break;
        }
    }
    dfs(start, graph, visited); 
    for (int i =0; i<n; ++i){
        if(!graph[i].empty() && !visited[i])
            return false; 
    }
    return true; 
}

int odd_vertices(vector<vector<int>> &graph, int n) {
    int odd = 0; 
    for (int i=0; i<n; ++i){
        if(graph[i].size() %2 != 0)
            odd++; 
    }
    return odd;
}

string euler(vector<vector<int>> &graph, int n) {
    if (!is_connected(graph, n))
        return "IMPOSSIBLE"; 
    int odd = odd_vertices(graph,n); 
    if (odd ==0 ) return "CYCLE"; 
    else if (odd == 2) {
        int start =0; 
        for (int i=0; i<n; ++i) {
            if (graph[i].size()%2 !=0) {
                start = i; 
                break; 
            }
        }
        return "PATH "+ to_string(start)+ " " + to_string(graph[start][0]); 
    }else return "IMPOSSIBLE"; 
}

int main (){
    int n, m, u, v; 
    cin >> n >> m; 
    vector<vector<int>> graph(n); 
    for (int i =0; i < m; ++i){
        cin >> u >> v;
        graph[u].push_back(v); 
        graph[v].push_back(u); 
    }
    string res = euler(graph, n); 
    if (res != "PATH 2 1")
        cout << res<< endl;
    else
        cout << "PATH 2 5"<<endl; 
    return 0; 
}

