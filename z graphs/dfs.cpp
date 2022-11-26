vector<vector<int>> g; vector<bool> visible;

void dfs(int cur) {
    visible[cur] = true;
    for(int s : g[cur]) {
        if(visible[s]) continue;
        dfs(s);
    }
}

void sol() {
    
    return;
}

int main() {
#ifndef ONLINE_JUDGE

    // For getting input from input.txt file
    freopen("input.txt", "r", stdin);

    // Printing the Output to output.txt file
    freopen("output.txt", "w", stdout);

#endif
    int t; cin >> t;
    while (t--) {
        sol();
    }
    return 0;
}
