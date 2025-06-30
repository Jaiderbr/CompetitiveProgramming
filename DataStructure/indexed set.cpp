#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template<class T> using T_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class L> using T_multiset = tree<L, null_type, less_equal<L>, rb_tree_tag, tree_order_statistics_node_update>;

/*
st.find_by_order(k) - Retorna un iterador al k-esimo elemento, >= sz .end()
st.order_of_key(k)  - Retorna el numero de elementos estrictamente menores que k
st.lower_bound(k)   - Retorna un iterador al primer elemento >= k, >= sz .end()
st.upper_bound(k)   - Retorna un iterador al primer elemento > k, >= sz .end()
st.erase(k)         - Elimina el elemento k
st.erase_if([](int x) { return x % 2 == 0; }); - Elimina todos los elementos que cumplan la condicion

T_set<int> st;
T_multiset<int> mst;
*/