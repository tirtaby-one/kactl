/**
 * Author: Johan Sannemo, pajenegod
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Range Minimum Queries on an array. Returns
 * min(V[a], V[a + 1], ... V[b - 1]) in constant time.
 * Usage:
 *  RMQ rmq(values);
 *  rmq.query(inclusive, exclusive);
 * Time: $O(|V| \log |V| + Q)$
 * Status: stress-tested
 */
#pragma once

vector<vector<ll>> st;
vector<int> lg;

void build(vector<ll>& a) {
    int n = sz(a), K = 32 - __builtin_clz(n);
    st.assign(K, vector<ll>(n));
    lg.assign(n + 1, 0);

    for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
    st[0] = a;

    for (int k = 1; k < K; k++)
        for (int i = 0; i + (1 << k) <= n; i++)
            st[k][i] = min(st[k-1][i], st[k-1][i+(1<<(k-1))]);
}

ll query(int l, int r) { // [l, r)
    int k = lg[r-l];
    return min(st[k][l], st[k][r-(1<<k)]);
}