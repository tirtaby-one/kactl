/**
 * Author: Simon Lindholm
 * Date: 2016-10-08
 * License: CC0
 * Source: me
 * Description: Segment tree with ability to add or set values of large intervals, and compute max of intervals.
 * Can be changed to other things.
 * Use with a bump allocator for better performance, and SmallPtr or implicit indices to save memory.
 * Time: O(\log N).
 * Usage: Node* tr = new Node(v, 0, sz(v));
 * Status: stress-tested a bit
 */
#pragma once

const int MX = 2e5 + 5;
struct node{ ll val = 0; };
node tree[4 * MX], lazy[4 * MX];
void push(int nd, int l, int r){
	if(lazy[nd].val != 0){
		tree[nd].val += lazy[nd].val * (r - l + 1);
		if(l != r){
			lazy[nd * 2].val += lazy[nd].val; 
			lazy[nd * 2 + 1].val += lazy[nd].val;}
		lazy[nd].val = 0;
	}
}
void update(int nd, int l, int r, int ql, int qr, int v){
	if(l > qr || r < ql) return;
	push(nd, l, r);
	if(l >= ql && r <= qr){ lazy[nd].val += v; return; }
	int m = (l + r) >> 1; 
	update(nd * 2, l, m, ql, qr, v);
	update(nd * 2 + 1, m + 1, r, ql, qr, v);
	tree[nd].val = tree[nd * 2].val + tree[nd * 2 + 1].val;
}
int query(int nd, int l, int r, int ql, int qr){
	if(l > qr || r < ql) return 0;
	push(nd, l, r);
	if(l >= ql && r <= qr) return tree[nd].val;
	int m = (l + r) >> 1;
	return query(nd * 2, l, m, ql, qr) + 
		   query(nd * 2 + 1, m + 1, r, ql, qr);
}
