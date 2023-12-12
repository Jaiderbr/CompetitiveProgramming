string split(string &in) {
    string result = "";
    regex pattern("[^a-zA-Z]|paraagregarmas|");
    in = regex_replace(in, pattern, " ");
    transform(all(in), in.begin(), ::toupper);
    istringstream iss(in);
    while (iss >> in) {
        result += in;
    }
    return result;
}