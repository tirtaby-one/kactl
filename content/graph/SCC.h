/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source: Czech graph algorithms book, by Demel. (Tarjan's algorithm)
 * Description: Finds strongly connected components in a
 * directed graph. If vertices $u, v$ belong to the same component,
 * we can reach $u$ from $v$ and vice versa.
 * Usage: scc(graph, [\&](vi\& v) { ... }) visits all components
 * in reverse topological order. comp[i] holds the component
 * index of a node (a component only has edges to components with
 * lower index). ncomps will contain the number of components.
 * Time: O(E + V)
 * Status: Bruteforce-tested for N <= 5
 */
#pragma once

vector<vector<int>> adj;
vector<int> disc, low, scc;
vector<bool> isinst;
stack<int> st;

int timer, scc_int;

void dfs(int cur) {
    disc[cur] = low[cur] = ++timer;
    st.push(cur); isinst[cur] = 1;
    for (auto it : adj[cur]) {
        if (disc[it] == 0) {
            dfs(it); low[cur] = min(low[cur], low[it]);
        } else if (isinst[it]) {
            low[cur] = min(low[cur], disc[it]);
        }
    }
    if (low[cur] == disc[cur]) {
        while (true) {
            int v = st.top(); st.pop();
            isinst[v] = 0;
            scc[v] = scc_int;
            if (v == cur) break;
        } scc_int++;
    }
}
void init_scc(int n) {
    disc.assign(n, 0), low.assign(n, 0), scc.assign(n, -1);
    isinst.assign(n, false);
    while (!st.empty()) st.pop();
    timer = scc_int = 0;
}
void find_scc(int n) {
    for(int i = 0; i < n; i++){ if(disc[i] == 0) dfs(i); }
}