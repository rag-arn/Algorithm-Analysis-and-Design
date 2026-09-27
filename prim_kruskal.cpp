#include<bits/stdc++.h>
using namespace std;

#define inf INT_MAX

double ans1 = 0;
double ans2 = 0;
int V, E;

class DSU {
    vector<int> parent;
    vector<int> rank;

    public :
    DSU (int n) {
        parent.resize(n);
        rank.resize(n);

        for (int i=0; i<n; i++) {
            parent[i] = i;
            rank[i] = 1;
        }
    }

    int find(int i) {
        if (parent[i]==i) return i;
        return find(parent[i]);
    }

    void uni (int x, int y) {
        int s1 = find(x), s2 = find(y);

        if (rank[s1]>rank[s2]) {
            parent[s2] = s1;
        }

        else if (rank[s1]<rank[s2]) {
            parent[s1] = s2;
        }
        
        else {
            parent[s1] = s2;
            rank[s2]++;
        }
    }
};

bool comparator (vector<int> a, vector<int> b) {
    return a[2]<b[2];
}

void kruskal (vector<vector<int>> lst) {
    sort (lst.begin(), lst.end(), comparator);
    vector<vector<int>> tree;

    DSU dsu(V);
    double cost = 0;
    int cnt = 0;

    for (auto it : lst) {
        int u = it[0];
        int v = it[1];
        int w = it[2];

        if (dsu.find(u)!=dsu.find(v)) {
            cnt++;
            dsu.uni(u, v);
            cost+=w;

            tree.push_back({u, v, w});

            if (cnt==V-1) {
                break;
            }
        }
    }

    for (auto it : tree) {
        cout << it[0] << " " << it[1] <<  " : " << it[2] << endl;
    }
    cout << "Total cost = " << cost << endl;
     ans2+=cost;
}

void prim (vector<vector<pair<int ,int>>> &lst, int src) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> parent(V, -1);
    vector<int> key(V, inf);
    vector<bool> vis(V, false);

    key[src] = 0;
    pq.push({0, src});

    double cost = 0;

    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();

        int u = top.second;

        if (vis[u]) {
            continue;
        }
        vis[u] = true;

        for (auto it : lst[u]) {
            int v = it.first, w = it.second;

            if (!vis[v] and w<key[v]) {
                key[v] = w;
                parent[v] = u;
                pq.push({w, v});
            }
        }
    }

    for (int i=0; i<V; i++) {
        if (parent[i]!=-1) {
            cout << parent[i] << " " << i << " : " << key[i] << endl;
            cost += key[i];
        }
    }
    cout << "Total cost = " << cost << endl;
    ans1 += cost;
}

void generate (vector<vector<pair<int, int>>> &lst) {
    set<pair<int, int>> st;
    
    int edge = (V*(V-1)/2);
    
    while (edge--) {
        int u = rand()%V, v = rand()%V;
        if (u==v) {
            edge++;
            continue;
        }
        if (u<v) swap(u, v);
        if (st.count({u, v})) {
            edge++;
            continue;
        }
        
        st.insert({u, v});
        int w = rand()%10000+1;
        
        lst[u].push_back({v, w});
        lst[v].push_back({u, w});
    }
}

void convert (vector<vector<pair<int, int>>> &lst, vector<vector<int>> &e_list) {
    int index = 0;
    for (int i=0; i<V; i++) {
        for (auto it : lst[i]) {
            if (i>it.first) {
                e_list[index] = {i, it.first, it.second};
                index++;
            }
        }
    }
}

int main() {
    srand(time(0));
    cin >> V;

    int E = (V*(V-1)/2);

    vector<vector<pair<int, int>>> lst1(V);
    vector<vector<pair<int, int>>> lst3(V);
    vector<vector<pair<int, int>>> lst2(V);
    
    generate(lst1);
    generate(lst2);
    generate(lst3);

    vector<vector<int>> e_list1(E);
    vector<vector<int>> e_list2(E);
    vector<vector<int>> e_list3(E);

    convert(lst1, e_list1);
    convert(lst2, e_list2);
    convert(lst3, e_list3);

    

    cout << "Prim information of tree 1 : " << endl;
    prim(lst1, 0);
    cout << endl;
    cout << endl;

    cout << "Prim information of tree 2 : " << endl;
    prim(lst2, 0);
    cout << endl;
    cout << endl;

    cout << "Prim information of tree 3 : " << endl;
    prim(lst3, 0);
    cout << endl;
    
    cout << "Total cost of the forest by Prim is " << ans1 << endl;
    cout << "\n\n\n" << endl;



    cout << "Kruskal information of tree 1 : " << endl;
    kruskal(e_list1);
    cout << endl;
    cout << endl;

    cout << "Kruskal information of tree 2 : " << endl;
    kruskal(e_list2);
    cout << endl;
    cout << endl;

    cout << "Kruskal information of tree 3 : " << endl;
    kruskal(e_list3);
    cout << endl;
    cout << endl;

    cout << "Total cost of the forest by Kruskal is " << ans2 << endl;
}
