/**
 * Author: Simon Lindholm
 * Date: 2016-01-14
 * License: CC0
 * Description: Given a rooted tree and a subset S of nodes, compute the minimal
 * subtree that contains all the nodes by adding all (at most $|S|-1$)
 * pairwise LCA's and compressing edges.
 * Returns a list of (par, orig\_index) representing a tree rooted at 0.
 * The root points to itself.
 * Time: $O(|S| \log |S|)$
 * Status: Tested at CodeForces
 */
#pragma once

// Requires: adj, depth, up, LOG, lca(u,v), init_lca(n,root)
// Node indexing: 0-based
typedef pair<int,int> pii;
typedef vector<pii> vpi;

vi tin, tout;
int timer_dfs;

void dfs_euler(int u, int p) {
    tin[u] = timer_dfs++;
    for(int v : adj[u]) {
        if(v == p) continue;
        dfs_euler(v, u);
    }
    tout[u] = timer_dfs;
}

void init_virtual_tree(int n, int root = 0) {
    tin.assign(n, 0);
    tout.assign(n, 0);
    timer_dfs = 0;
    dfs_euler(root, -1);
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

vpi compress_tree(vi subset) {
    sort(all(subset), [&](int u, int v){
        return tin[u] < tin[v];
    });

    int m = sz(subset);
    if (m == 0) return {};

    vi nodes = subset;
    rep(i, 0, m-1) {
        nodes.push_back(lca(subset[i], subset[i+1]));
    }

    sort(all(nodes), [&](int u, int v) {
        return tin[u] < tin[v];
    });
    nodes.erase(unique(all(nodes)), nodes.end());

    vpi ret;
    vi st, par(sz(nodes));

    rep(i, 0, sz(nodes)) {
        while(!st.empty() && !is_ancestor(nodes[st.back()], 
			nodes[i])){ st.pop_back(); }

        if(st.empty()) par[i] = i;
        else par[i] = st.back()
        st.push_back(i);
    }

    ret.emplace_back(0, nodes[0]);
    rep(i, 1, sz(nodes)){ ret.emplace_back(par[i], nodes[i]);}

    return ret;
}