/**
 * Author: Simon Lindholm
 * Date: 2017-05-11
 * License: CC0
 * Source: folklore
 * Description: Computes sums a[i,j] for all i<I, j<J, and increases single elements a[i,j].
 *  Requires that the elements to be updated are known in advance (call fakeUpdate() before init()).
 * Time: $O(\log^2 N)$. (Use persistent segment trees for $O(\log N)$.)
 * Status: stress-tested
 */
#pragma once

vector<vector<int>> ys;
vector<vector<ll>> bt2;

// Daftarkan koordinat (x, y) sebelum init().
void fake_update(int x, int y) {
    for (; x < sz(ys); x += x & -x) { ys[x].push_back(y); }
}

// Inisialisasi seluruh Fenwick Tree bagian dalam.
void init() {
    for (int x = 1; x < sz(ys); x++) {
        sort(all(ys[x]));
        ys[x].erase(unique(all(ys[x])), ys[x].end());
        bt2[x].assign(sz(ys[x]) + 1, 0);
    }
}

// Posisi one-based y di dalam koordinat terkompresi.
int ind(int x, int y) { 
    return (int)(lower_bound(all(ys[x]), y)-ys[x].begin()) + 1;}

// Tambahkan dif pada titik (x, y).
void update(int x, int y, ll dif) {
    for (; x < sz(ys); x += x & -x) {
        int p = ind(x, y);
        for (;p < sz(bt2[x]); p += p & -p) { bt2[x][p] += dif; }
    }
}

// Jumlah nilai untuk titik dengan koordinat X <= x dan Y <= y.
ll query(int x, int y) {
    ll res = 0;
    for (; x > 0; x -= x & -x) {
        int p = (int)(upper_bound(all(ys[x]), y)-ys[x].begin());
        for (; p > 0; p -= p & -p) { res += bt2[x][p]; }
    }
    return res;
}