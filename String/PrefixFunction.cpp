//Dado un string s retorna un vector pf donde pf[i] es el largo del prefijo propio mas largo que tambien es sufijo de s[0] hasta s[i].
//For example, prefix function of string "abcabcd" is  [0, 0, 0, 1, 2, 3, 0], and prefix function of string "aabaaab" is [0, 1, 0, 1, 2, 2, 3].
//Complejidad: O(| n | )

vector<int> prefix_function(string& s) {
    int n = s.size();
    vector<int> pf(n);
    pf[0] = 0;
    for (int i = 1, j = 0; i < n; i++) {
        while (j && s[i] != s[j]) j = pf[j - 1];
        if (s[i] == s[j]) j++;
        pf[i] = j;
    }
    return pf;
}