/**
 * Author: someone on Codeforces
 * Date: 2017-03-14
 * Source: folklore
 * Description: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits/joins, and
 *  is easy to augment with additional data.
 * Time: $O(\log N)$
 * Status: stress-tested
 */
#pragma once

const int MAXN = 200005;
int lch[MAXN], rch[MAXN];
int val[MAXN], pri[MAXN], cnt[MAXN];
int nodes = 0;

int new_node(int v) {
    int n = ++nodes;
    lch[n] = rch[n] = 0;
    val[n] = v;
    pri[n] = rand();
    cnt[n] = 1;
    return n;
}

int sz(int n) { return n ? cnt[n] : 0; }
void recalc(int n) { if (n) cnt[n] = sz(lch[n]) + sz(rch[n]) + 1; }

void each(int n) {
    if (!n) return;
    each(lch[n]);
    cout << val[n] << ' ';
    each(rch[n]);
}

// Split into first k elements and the remaining elements.
pair<int, int> split(int n, int k) {
    if (!n) return {0, 0};

    if (sz(lch[n]) >= k) {
        auto [L, R] = split(lch[n], k);
        lch[n] = R;
        recalc(n);
        return {L, n};
    } else {
        auto [L, R] = split(rch[n], k - sz(lch[n]) - 1);
        rch[n] = L;
        recalc(n);
        return {n, R};
    }
}

int merge(int a, int b) {
    if (!a) return b;
    if (!b) return a;

    if (pri[a] > pri[b]) {
        rch[a] = merge(rch[a], b);
        recalc(a);
        return a;
    } else {
        lch[b] = merge(a, lch[b]);
        recalc(b);
        return b;
    }
}

// Insert treap b at index pos in treap t.
int ins(int t, int b, int pos) {
    auto [a, c] = split(t, pos);
    return merge(merge(a, b), c);
}

// Move range [l, r) to index k.
// k is the insertion index in the original sequence.
void move_range(int &t, int l, int r, int k) {
    if (l >= r || k >= l && k <= r) return;

    auto [a, bc] = split(t, l);
    auto [b, c] = split(bc, r - l);

    if (k < l) {
        t = merge(ins(a, b, k), c);
    } else {
        t = merge(a, ins(c, b, k - r));
    }
}

int main() {
    srand(time(nullptr));
    int root = 0;
    // Example: sequence [10, 20, 30, 40, 50]
    for (int x : {10, 20, 30, 40, 50}) {
        root = merge(root, new_node(x));
    }

    move_range(root, 1, 3, 5); // Move [20, 30] to the end.
    each(root);
    cout << '\n';
}