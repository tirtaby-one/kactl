/**
 * Author: Simon Lindholm
 * Date: 2017-04-20
 * License: CC0
 * Source: own work
 * Description: Container where you can add lines of the form kx+m, and query maximum values at points x.
 *  Useful for dynamic programming (``convex hull trick'').
 * Time: O(\log N)
 * Status: stress-tested
 */
#pragma once

struct Line {
    ll k, m;
    mutable ll p;
};

struct Cmp {
    using is_transparent = void;
    bool operator()(const Line& a, const Line& b) const{
        return a.k < b.k;}
    bool operator()(const Line& a, ll x) const{ return a.p < x; }
    bool operator()(ll x, const Line& a) const{ return x < a.p; }
};

multiset<Line, Cmp> hull;
const ll INF = LLONG_MAX;
ll divfloor(ll a, ll b){ return a / b - ((a ^ b) < 0 && a % b); }

bool isect(multiset<Line, Cmp>::iterator x,
    multiset<Line, Cmp>::iterator y) {
    if(y == hull.end()){ x->p = INF; return false; }
    if(x->k == y->k){ x->p = (x->m > y->m ? INF : -INF); }
	else{ x->p = divfloor(y->m - x->m, x->k - y->k); }
    return x->p >= y->p;
}

void addline(ll k, ll m) {
    auto z = hull.insert({k, m, 0});
    auto y = z++;
    auto x = y;

    while(isect(y, z)){ z = hull.erase(z); }
    if (x != hull.begin() && isect(--x, y)){
        isect(x, y = hull.erase(y)); }
    while((y = x) != hull.begin() && (--x)->p >= y->p){
        isect(x, hull.erase(y)); }
}

ll query(ll x) {
    assert(!hull.empty());
    auto it = *hull.lower_bound(x);
    return it.k * x + it.m;
}