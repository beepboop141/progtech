#include<iostream>
#include <bits/stdc++.h>
using namespace std; 

class Graph {
  private:
    int V; 
    list<int> *adj;

    vector<int> path; 
    bool cyclic_aux(int v, bool visited[], bool recursion_stack[], vector<int> &path) const {
    if (visited[v] == false) {
        visited[v] = true;
        recursion_stack[v] = true;
        for (int i : adj[v]) {
            if (!visited[i] && cyclic_aux(i, visited, recursion_stack, path)) {
                path.push_back(v);
                return true;
            } else if (recursion_stack[i] && i != v) {
                path.push_back(i);
                path.push_back(v);
                return true;
            }
        }
    }
    recursion_stack[v] = false;
    return false;
}

  public: 
    Graph(int v): V(v), adj(new list<int>[v]) {}
    ~Graph() { delete[] adj;}
    void addEdge(int u, int v) {
        if (u != v) {
          bool foo = true;
        for (const auto &b : adj[u]) {
            if (b == v) { 
                foo = false; 
                break; 
            }
        }
            if(foo) adj[u].push_back(v); 
        }
    }
    bool cycle(vector<int> &path) const {
      bool visited[V]; 
      bool recursion_stack[V];
      for (int i =0; i<V; ++i){
        visited[i] = false; 
        recursion_stack[i] = false; 
      }
      for (int i =0; i < V; ++i) {
       if(cyclic_aux(i, visited, recursion_stack, path)){
          reverse(path.begin(), path.end()); 
          if (path.size() > 1 && path.front() == path.back()) {
            path.pop_back();
            }          
        return true; 
       }
      } return false; 
    }
};
    
#ifndef CONTEST
int main() {
  int V, E;
  cin >> V >> E;
  Graph g(V);
  for(int i = 0; i < E; i++) {
    int u, v;
    cin >> u >> v;
    g.addEdge(u, v);
  }
  vector<int> path;
  bool c = g.cycle(path);
  if(c) {
    cout << "CYCLE: ";
    for(unsigned i = 0; i < path.size(); i++)
      cout << path[i] << (i == path.size() - 1 ? "\n" : " ");
  } else {
    cout << "NO CYCLE" << endl;
  }
}
#endif