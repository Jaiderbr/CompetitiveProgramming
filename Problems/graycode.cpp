/*
Genera una permutación de 0 a 2^n-1, de modo que
dos posiciones adyacentes difieren en exactamente 1 bit
*/

vector<string> gray_code(int n) {
    vector<string> ret(1 << n);
    for (int i = 0; i < (1 << n); i++) {
        ret[i] = bitset<32>(i ^ (i >> 1)).to_string();
    }
    return ret;
}
