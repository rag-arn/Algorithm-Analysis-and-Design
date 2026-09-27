#include<bits/stdc++.h>
using namespace std;
int V, E;

bool bfs (vector<vector<int>> &rgraph, int src, int sink, vector<int> &parent) {
    queue<int> q;
    q.push(src);
    vector<bool> vis(V, false);
    vis[src] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v=0; v<V; v++) {
            if (!vis[v] and rgraph[u][v]>0) {
                parent[v] = u;
                vis[v] = true;

                if (v==sink) {
                    return true;
                }
                q.push(v);
            }
        }
    }
    return false;
}

void max_flow(vector<vector<int>> lst) {
    vector<vector<int>> graph(V, vector<int> (V, 0));

    for (auto it : lst) {
        int u = it[0];
        int v = it[1];
        int w = it[2];
        graph[u][v] = w;
    }
    vector<vector<int>> rgraph = graph;

    int src = 0, sink = V-1;
    vector<int> parent (V);

    int max_flow = 0;

    while (bfs(rgraph, src, sink, parent)) {
        int bottleNeck = INT_MAX;

        for (int v=sink; v!=src; v=parent[v]) {
            int u = parent[v];
            bottleNeck = min(bottleNeck, rgraph[u][v]);
        }

        for (int v=sink; v!=src; v=parent[v]) {
            int u = parent[v];
            rgraph[u][v] -= bottleNeck;
            rgraph[v][u] += bottleNeck;
        }
        max_flow += bottleNeck;
    }
    cout << max_flow << endl;
}


int main() {
    cin >> V >> E;

    vector<vector<int>> lst(E);
    set<pair<int, int>> st;

    int index = 0;

    int edge = E;
    while (edge--) {
        int u, v, x;
        cin >> u >> v >> x;

        lst[index] = {u, v, x};
        index++;
    }

    max_flow(lst);
}
