#include<bits/stdc++.h>
using namespace std;

#define inf INT_MAX

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

void generate (vector<vector<int>> lst, vector<int> chosen, int idx, int wt) {
    if (chosen.size()==V-1) {
        for (int i : chosen) {
            cout << lst[i][0] << "-" << lst[i][1] << "(" << lst[i][2] << ") ";
        }
        cout << "| Cost = " << wt << endl;
        
        return;
    }

    if (idx==E or E-idx<V-1-chosen.size()) {
        return;
    }

    DSU dsu(V);
    for (auto it : chosen) {
        dsu.uni(lst[it][0], lst[it][1]);
    }

    int u = lst[idx][0];
    int v = lst[idx][1];
    int w = lst[idx][2];

    if (dsu.find(u)!=dsu.find(v)) {
        chosen.push_back(idx);
        generate(lst, chosen, idx+1, w+wt);
        chosen.pop_back();
    }
    generate(lst, chosen, idx+1, wt);
}


int main() {
    cin >> V >> E;
    srand(time(0));

    vector<vector<int>> lst(E);
    set<pair<int, int>> st;

    int index = 0;

    int edge = E;
    while (edge--) {
        int u = rand()%V, v = rand()%V;
        if (u==v) {
            edge++;
            continue;
        }

        if (st.count({u, v})) {
            edge++;
            continue;
        }
        st.insert({u, v});

        int w = rand()%10001;

        lst[index] = {u, v, w};
        index++;
    }

    vector<int> chosen;
    generate(lst, chosen, 0, 0);
}
