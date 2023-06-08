#include <iostream>
#include <vector>
using namespace std; 

class UnionFind {
private:
    vector<int> parent;
    vector<int> size;
    int count;

public:
    UnionFind(int n) {
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        count = n;
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        while (x != parent[x]) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    void unionSets(int p, int q) {
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP == rootQ) {
            return;
        }
        if (size[rootP] < size[rootQ]) {
            parent[rootP] = rootQ;
            size[rootQ] += size[rootP];
        } else {
            parent[rootQ] = rootP;
            size[rootP] += size[rootQ];
        }
        count--;
    }

    int getCount() {
        return count;
    }
};

int minimumGroups(int N, int M, int K, const vector<pair<int, int>>& roads) {
    UnionFind unionFind(N);
    for (const auto& road : roads) {
        int A = road.first;
        int B = road.second;
        unionFind.unionSets(A, B);
    }
    int minGroups = unionFind.getCount() - K;
    return minGroups;
}

int main() {
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);
    vector<pair<int, int>> roads;
    for (int i = 0; i < M; ++i) {
        int A, B;
        scanf("%d %d", &A, &B);
        roads.push_back({ A, B });
    }
    int result = minimumGroups(N, M, K, roads);
    if (result == -1 || result == 0) cout << 1 << endl;
    else cout << result <<endl;
    return 0;
}
