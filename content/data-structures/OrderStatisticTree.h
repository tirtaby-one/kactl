/**
 * Author: Simon Lindholm
 * Date: 2016-03-22
 * License: CC0
 * Source: hacKIT, NWERC 2015
 * Description: A set (not multiset!) with support for finding the n'th
 * element, and finding the index of an element.
 * To get a map, change \texttt{null\_type}.
 * Time: O(\log N)
 */
#pragma once

#include <bits/extc++.h> /** keep-include */
using namespace __gnu_pbds;

template<class T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag,
    tree_order_statistics_node_update>;

void example() {
	Tree<int> t, t2; t.insert(v[0]), t.insert(v[1]);
	int val = *t.find_by_order(idx); // idx-th smallest val
	int val2 = 	t.order_of_key(tg); // how many number < tg 
	st.erase(num); // erase element num
	join(t, t2); // All t2 val > t1 val, then t2 wl cleared
}
