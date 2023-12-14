/*
Dado N pesos y un limite Q, se quiere saber el minimo numero
de grupos en los que se pueden dividir los pesos tal que la
suma de los pesos de cada grupo sea menor o igual a Q
n => sz(nums);
q => maximo peso
nums => vector con los pesos
*/
int calculate(int n, int q, vector<int>& nums) {
    pair<int, int> best[1 << n];
    best[0] = { 1,0 };
    forne(i, 1, 1 << n) {
        best[i] = { n + 1,0 };
        forn(j, n) {
            if (i & (1 << j)) {
                auto cur = best[i ^ (1 << j)];
                if (cur.s + nums[j] <= q) {
                    cur.s += nums[j];
                }
                else {
                    cur.f++;
                    cur.s = nums[j];
                }
                best[i] = min(best[i], cur);
            }
        }
    }
    return best[(1 << n) - 1].f;
}


/*
Dado N pesos y un limite Q, se quiere saber el numero de grupos
consecutivos en los que se pueden dividir los pesos tal que la
suma de los pesos de cada grupo sea menor o igual a Q
n => sz(nums);
q => maximo peso
nums => vector con los pesos
*/

int CalculateLineal(int n, int q, vector<int>& nums) {
    int cnt = 0;
    int currSUM = 0;
    forn(i, n) {
        if (nums[i] + currSUM > q) {
            cnt++;
            currSUM = 0;
        }
        currSUM += nums[i];
    }
    return cnt + (currSUM > 0);
}
