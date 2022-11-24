
vector<vector<int>> g; vector<bool> visible;
void bfs(vector<int>& starts) {
    for(int x : starts)
       visible[x]=true;
    vector<int> cur_level=starts;
    int dist=0;
    while (!cur_level.empty()) {
        vector<int> next_level;
        for(int f : cur_level) {
            for(int s : g[f]) {
                if (visible[s]) continue;
                visible[s]=true;
                next_level.push_back(s);
            }
        }
    cur_level = next_level;
        dist++;
    }
}
