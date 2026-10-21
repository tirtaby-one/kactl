/**
 * Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed sum-tree.
 * Can be changed by modifying T, f and unit.
 * Time: O(\log N)
 * Status: stress-tested
 */
#pragma once

const int MX = 2e5 + 5;
struct node{ int val = 0; };
node tree[4 * MX];
int arr[MX];
void update(int nd, int l, int r, int p, int v){
	if(l > p || r < p) return;
	if(l == r){ tree[nd].val = v; return; }
	int m = (l + r) >> 1; 
	update(nd * 2, l, m, p, v);
	update(nd * 2 + 1, m + 1, r, p, v);
	tree[nd].val = tree[nd * 2].val + tree[nd * 2 + 1].val;
}
int query(int nd, int l, int r, int ql, int qr){
	if(l > qr || r < ql) return 0;
	if(l >= ql && r <= qr) return tree[nd].val;
	int m = (l + r) >> 1;
	return query(nd * 2, l, m, ql, qr) + 
		   query(nd * 2 + 1, m + 1, r, ql, qr);
}
