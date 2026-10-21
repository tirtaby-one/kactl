/**
 * Author: Lukas Polacek
 * Date: 2009-10-30
 * License: CC0
 * Source: folklore/TopCoder
 * Description: Computes partial sums a[0] + a[1] + ... + a[pos - 1], and updates single elements a[i],
 * taking the difference between the old and new value.
 * Time: Both operations are $O(\log N)$.
 * Status: Stress-tested
 */
#pragma once

vector<ll> bt;
void update(int p, int val){ 
    for(;p < sz(bt); p += (p & -(p))) bt[p] += val; }
int query(int p){
	ll res = 0;
	for(;p;p -= (p & -(p))) res += bt[p];
	return res;
}
int low_bound(ll sum){
	if (sum <= 0) return 0;
    int pos = 0;
    for (int pw = 1 << 25; pw; pw >>= 1) {
        if (pos + pw < sz(bt) && bt[pos + pw] < sum) {
            pos += pw;
            sum -= bt[pos];
        }
    }
    return pos + 1;
}