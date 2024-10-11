Dado un string s devuelve el indice donde comienza la rotación lexicograficamente menor de s.

int minimum_expression(string s) { //Factorizacion de lyndon
    s = s+s; // si no se concatena devuelve el indice del sufijo menor
    int len = s.size(), i = 0, j = 1, k = 0;
    while (i+k < len && j+k < len) {
        if (s[i+k] == s[j+k]) k++;
        else if (s[i+k] > s[j+k]) i = i+k+1, k = 0; // cambiar por < para maximum
        else j = j+k+1, k = 0;
        if (i == j) j++;
    }
    return min(i, j);
}


/*
max_suffix: retorna el inicio del sufijo lexicograficamente mayor
min_suffix: retorna el inicio del sufijo lexicograficamente menor
max_cyclic_shift: retorna el inicio del shift ciclico lexicograficamente mayor
min_cyclic_shift: retorna el inicio del shift ciclico lexicograficamente menor
*/
template<typename T> int max_suffix(T s, bool mi = false) {
    s.push_back(*min_element(s.begin(), s.end()) - 1);
    int ans = 0;
    for (int i = 1; i < s.size(); i++) {
        int j = 0;
        while (ans + j < i && s[i + j] == s[ans + j]) j++;
        if (s[i + j] > s[ans + j]) {
            if (!mi or i != s.size() - 2) ans = i;
        }
        else if (j) i += j - 1;
    }
    return ans;
}

template<typename T> int min_suffix(T s) {
    for (auto& i : s) i *= -1;
    s.push_back(*max_element(s.begin(), s.end()) + 1);
    return max_suffix(s, true);
}

template<typename T> int max_cyclic_shift(T s) {
    int n = s.size();
    for (int i = 0; i < n; i++) s.push_back(s[i]);
    return max_suffix(s);
}

template<typename T> int min_cyclic_shift(T s) {
    for (auto& i : s) i *= -1;
    return max_cyclic_shift(s);
}
