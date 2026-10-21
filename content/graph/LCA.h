/**
 * Author: chilli, pajenegod
 * Date: 2020-02-20
 * License: CC0
 * Source: Folklore
 * Description: Data structure for computing lowest common ancestors in a tree
 * (with 0 as root). C should be an adjacency list of the tree, either directed
 * or undirected.
 * Time: $O(N \log N + Q)$
 * Status: stress-tested
 */
#pragma once

int LOG;
vector<vi> adj, up;
vi depth;

void dfs_lca(int u, int p) {
    up[0][u] = p;
    for (int k = 1; k < LOG; k++) up[k][u] = up[k-1][up[k-1][u]];
    for (int v : adj[u]) {
        if (v == p) continue;
        depth[v] = depth[u] + 1;
        dfs_lca(v, u);
    }
}

void init_lca(int n, int root = 0) {
    LOG = 1;
    while ((1 << LOG) <= n) LOG++;

    up.assign(LOG, vi(n, root));
    depth.assign(n, 0);
    dfs_lca(root, root);
}

int kth_ancestor(int u, int k) {
    for (int i = 0; i < LOG; i++) if(k >> i & 1) u = up[i][u];
    return u;
}

int lca(int u, int v) {
    i(depth[u] < depth[v]) swap(u, v);

    u = kth_ancestor(u, depth[u] - depth[v]);
    if(u == v) return u;

    for(int k = LOG-1; k >= 0; k--) {
        if(up[k][u] != up[k][v]) {
            u = up[k][u];
            v = up[k][v];
        }
    }
    return up[0][u];
}

int dist(int u, int v) {
    return depth[u] + depth[v] - 2 * depth[lca(u, v)];
}