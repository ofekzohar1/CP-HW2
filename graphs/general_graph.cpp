
vector<vector<int>> g; 


void create_and_parse_undirected_graph(int n, int m) {
    g = VVI(n+1);
    for (int i = 1; i <= m; i++) {
        int a_i, b_i; cin >> a_i >> b_i;
        g[a_i].push_back(b_i);
        g[b_i].push_back(a_i);
    }
}

void create_and_parse_directed_graph(int n, int m) {
    g = VVI(n+1);
    for (int i = 1; i <= m; i++) {
        int a_i, b_i; cin >> a_i >> b_i;
        g[a_i].push_back(b_i);
    }
}
