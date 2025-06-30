template<typename T>
T split(string& in) {
    T result;
    regex pattern("[^a-zA-Z]|paraagregarmas | |");
    in = regex_replace(in, pattern, " ");
    transform(all(in), in.begin(), ::toupper);
    istringstream iss(in);
    string token;
    if constexpr (is_same<T, vector<string>>::value) while (iss >> token) result.pb(token);
    else if constexpr (is_same<T, string>::value) {
        result = ""; while (iss >> token) result += token;
    }
    return result;
}