
vector<vector<int>> g; vector<bool> visible;
vector<vector<int>> children;

// parent & adj list version
void dfs_tree(int V, int pV) {
    for(int s : g[V]) {
        if(s != pV) {
            dfs_tree(s, V);
        }
    }
}

// children version
void dfs_tree(int V) {
    for(int s : children[V]) {
        dfs_tree(s);
    }
}

// get children of the bfs tree of root.
void get_children_of_tree_from_undirected_graph(int n, int root) {
    children = vector<vector<int>>(n+1);
    vector<bool> already_handled = vector<bool>(n+1);
    already_handled[root] = true;

    vector<int> cur_level={root};
    while (!cur_level.empty()) {
        vector<int> next_level;
        for(int cur_node : cur_level) {
            for(int child : g[cur_node]) {
                if (already_handled[child]) continue;
                children[cur_node].push_back(child);
                already_handled[child]=true;
                next_level.push_back(child);
            }
        }
    cur_level = next_level;
    }
}
