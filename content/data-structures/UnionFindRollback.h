/**
 * Author: Lukas Polacek, Simon Lindholm
 * Date: 2019-12-26
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set data structure with undo.
 * If undo is not needed, skip st, time() and rollback().
 * Usage: int t = uf.time(); ...; uf.rollback(t);
 * Time: $O(\log(N))$
 * Status: tested as part of DirectedMST.h
 */
#pragma once

vi par; vector<pii> st;
void init(int n){ par.assign(n, -1); st.clear(); }
int fpar(int x){ if(par[x]<0)return x; return fpar(par[x]); }
int szz(int x){ return -par[fpar(x)]; } // CC Size
int time(){ return st.size(); } // roll back to t=time()
int roll(int t){ while(time() > t){
		auto [x, val] = st.back(); st.pop_back();
		par[x] = val;
	}
}
bool join(int a, int b){
	a = fpar(a), b = fpar(b);
	if(a == b) return false;
	if(par[a] > par[b]) swap(a, b);
	st.push_back({a, par[a]});
	st.push_back({b, par[b]});
	par[a] += par[b], par[b] = a;
	return true;
}