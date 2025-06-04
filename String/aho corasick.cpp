// Esta version de aho_corasick usa un bitmask de tamano ALPHABET, por lo que debe ser modificado para ALPHABET > 26.        
// suff = el indice del nodo del sufijo estricto mas largo del nodo actual que tambien esta en el arbol.
// dict = el indice del nodo del sufijo estricto mas largo del nodo actual que esta en la lista de palabras.
// depth = profundidad normal del trie (la raiz es 0). Se puede eliminar para ahorrar memoria.
// word_index = el indice de la *primera* palabra que termina en este nodo. -1 si no hay ninguna.
// word_count = el numero total de palabras que terminan en este nodo. Usado en count_total_matches().
// first_child = el primer hijo de este nodo (los hijos son secuenciales debido al orden BFS), -1 si no hay ninguno.
// child_mask = la mascara de bits de las claves de los hijos disponibles desde este nodo. Si ALPHABET > 26, cambie el tipo.

const int INF = int(1e9) + 5;
template<char MIN_CHAR = 'a', typename mask_t = uint32_t>
struct aho_corasick {
    struct node {
        int suff = -1, dict = -1, depth = 0, word_index = -1, word_count = 0, first_child = -1;
        mask_t child_mask = 0;
        int get_child(char c) const {
            int bit = c - MIN_CHAR;
            if ((child_mask >> bit & 1) == 0) return -1;
            assert(first_child >= 0);
            return first_child + __builtin_popcount(child_mask & ((mask_t(1) << bit) - 1));
        }
    };

    vector<node> nodes;
    int W = 0;
    vector<int> word_location, word_indices_by_depth, defer;

    aho_corasick(const vector<string>& words = {}) { build(words); }

    // construir la adj list basada en los suffix parents. A menudo queremos realizar DP y/o consultas en este arbol.
    vector<vector<int>> build_suffix_adj() const {
        vector<vector<int>> adj(sz(nodes));
        forne(i, 1, sz(nodes)) adj[nodes[i].suff].push_back(i);
        return adj;
    }

    int get_or_add_child(int current, char c) {
        int bit = c - MIN_CHAR;
        if (nodes[current].child_mask >> bit & 1) return nodes[current].get_child(c);
        assert(nodes[current].child_mask >> bit == 0);
        int index = sz(nodes);
        nodes[current].child_mask |= mask_t(1) << bit;
        if (nodes[current].first_child < 0) nodes[current].first_child = index;
        nodes.emplace_back();
        nodes.back().depth = nodes[current].depth + 1;
        return index;
    }

    // return donde en el trie deberiamos terminar despues de comenzar en "location" y agregar el char "C".
    // corre en el peor de los casos O(depth) pero se amortiza a O(1) en la mayoria de las situaciones.
    int get_suffix_link(int location, char c) const {
        int child;
        while (location >= 0 && (child = nodes[location].get_child(c)) < 0) location = nodes[location].suff;
        return location < 0 ? 0 : child;
    }

    void build(const vector<string>& words) {
        nodes = { node() };
        W = sz(words);
        vector<int> indices(W);
        iota(all(indices), 0);
        stable_sort(all(indices), [&](int a, int b) -> bool { return words[a] < words[b]; });
        word_location.assign(W, 0);
        vector<int> remaining = indices;
        int rem = W;

        for (int depth = 0; rem > 0; depth++) {
            int nrem = 0;
            forn(i, rem) {
                int word = remaining[i];
                int& location = word_location[word];
                if (depth >= int(words[word].size())) {
                    if (nodes[location].word_index < 0) nodes[location].word_index = word;
                    nodes[location].word_count++;
                }
                else {
                    location = get_or_add_child(location, words[word][depth]);
                    remaining[nrem++] = word;
                }
            }
            rem = nrem;
        }

        int max_depth = 0;
        defer.resize(W);

        forn(i, W) {
            max_depth = max(max_depth, int(words[i].size()));
            defer[i] = nodes[word_location[i]].word_index;
        }
        // crear una lista de indices de palabras en orden decreciente de profundidad, en tiempo lineal a traves de counting sort.
        word_indices_by_depth.resize(W);
        vector<int> depth_freq(max_depth + 1, 0);
        forn(i, W) depth_freq[words[i].size()]++;
        for (int i = max_depth - 1; i >= 0; i--)  depth_freq[i] += depth_freq[i + 1];
        for (int i = W - 1; i >= 0; i--) word_indices_by_depth[--depth_freq[words[i].size()]] = i;

        // Solve suffix parents by traversing in order of depth (BFS order).

        forn(i, sz(nodes)) {
            mask_t child_mask = nodes[i].child_mask;
            while (child_mask != 0) {
                int bit = __builtin_ctzll(child_mask);
                char c = char(MIN_CHAR + bit);
                int index = nodes[i].get_child(c);
                child_mask ^= mask_t(1) << bit;
                // buscamos el suffix parent de index, que es el suffix parent de i que tiene un hijo c.
                int suffix_parent = get_suffix_link(nodes[i].suff, c);
                nodes[index].suff = suffix_parent;
                nodes[index].word_count += nodes[suffix_parent].word_count;
                nodes[index].dict = nodes[suffix_parent].word_index < 0 ? nodes[suffix_parent].dict : suffix_parent;
            }
        }
    }
 
    // Counts the number of matches of each word in O(text length + num words).
    vector<int> count_matches(const string& text) const {
        vector<int> matches(W, 0);
        int current = 0;
        for (char c : text) {
            current = get_suffix_link(current, c);
            int dict_node = nodes[current].word_index < 0 ? nodes[current].dict : current;
            if (dict_node >= 0) matches[nodes[dict_node].word_index]++;
        }

        // Iterate in decreasing order of depth.
        for (int word_index : word_indices_by_depth) {
            int location = word_location[word_index];
            int dict_node = nodes[location].dict;
            if (dict_node >= 0) matches[nodes[dict_node].word_index] += matches[word_index];
        }
        forn(i, W) matches[i] = matches[defer[i]];
        return matches;
    }

    // Finds the last index of the first occurrence of each word (INF if not present) in O(text length + num words).
    vector<int> find_first_occurrence(const string& text) const {
        vector<int> first_occurrence(W, INF);
        int current = 0;
        forn(i, sz(text)) {
            char c = text[i];
            current = get_suffix_link(current, c);
            int dict_node = nodes[current].word_index < 0 ? nodes[current].dict : current;
            if (dict_node >= 0) {
                int word = nodes[dict_node].word_index;
                first_occurrence[word] = min(first_occurrence[word], i);
            }
        }

        // Iterate in decreasing order of depth.
        for (int word_index : word_indices_by_depth) {
            int location = word_location[word_index];
            int dict_node = nodes[location].dict;

            if (dict_node >= 0) {
                int word_parent = nodes[dict_node].word_index;
                first_occurrence[word_parent] = min(first_occurrence[word_parent], first_occurrence[word_index]);
            }
        }

        forn(i, W) first_occurrence[i] = first_occurrence[defer[i]];
        return first_occurrence;
    }


    vector<int> find_last_occurrence(const string& text) const {
        vector<int> first_occurrence(W, -INF);
        int current = 0;
        forn(i, sz(text)) {
            char c = text[i];
            current = get_suffix_link(current, c);
            int dict_node = nodes[current].word_index < 0 ? nodes[current].dict : current;
            if (dict_node >= 0) {
                int word = nodes[dict_node].word_index;
                first_occurrence[word] = max(first_occurrence[word], i);
            }
        }

        // Iterate in decreasing order of depth.
        for (int word_index : word_indices_by_depth) {
            int location = word_location[word_index];
            int dict_node = nodes[location].dict;

            if (dict_node >= 0) {
                int word_parent = nodes[dict_node].word_index;
                first_occurrence[word_parent] = max(first_occurrence[word_parent], first_occurrence[word_index]);
            }
        }
        forn(i, W) first_occurrence[i] = first_occurrence[defer[i]];
        return first_occurrence;
    }

    // Counts the number of matches over all words at each ending position in "text" in O(text length).
    vector<int> count_matches_by_position(const string& text) const {
        vector<int> matches(sz(text));
        int current = 0;
        forn(i, sz(text)) {
            current = get_suffix_link(current, text[i]);
            matches[i] = nodes[current].word_count;
        }

        return matches;
    }

    // Counts the total number of matches of all words within "text" in O(text length).
    int64_t count_total_matches(const string& text) const {
        int64_t matches = 0;
        int current = 0;
        for (char c : text) {
            current = get_suffix_link(current, c);
            matches += nodes[current].word_count;
        }
        return matches;
    }
};
