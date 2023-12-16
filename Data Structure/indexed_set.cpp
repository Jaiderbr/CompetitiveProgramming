#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<class T> using T_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class L> using T_multiset = tree<L, null_type, less_equal<L>, rb_tree_tag, tree_order_statistics_node_update>;
/*
T_set<int> st;
st.insert(1);
st.insert(3);
st.insert(4);
st.insert(10);

The function find_by_order returns an iterator to the element at a given position
auto it = *st.find_by_order(1); it = {3}

the function order_of_key returns the position of a given element
int pos = st.order_of_key(4); pos = 2

If the element does not appear in the set, we get the position that the
element would have in the set
int pos = st.order_of_key(6); pos2 = 3
int pos = st.order_of_key(2); pos2 = 1

st.erase_if([](int x) {return x == 2 || x == 10;});









*/