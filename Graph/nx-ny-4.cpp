vector<vector<char>>board;
vector<vector<bool>>vis;
int n, m;
// R D L U 
int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };
void init() {
    board.resize(n + 1, vector<char>(m + 1));
    vis.resize(n + 1, vector<bool>(m + 1, 0));
}

void back(int x, int y) {
    vis[x][y] = 1;
    forn(i, 4) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && board[nx][ny] != '1' && !vis[nx][ny]) back(nx, ny);
    }
}
