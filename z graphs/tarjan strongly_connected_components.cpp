
/*
 *
 Tarjan's algorithm for finding strongly connected components (SCC)

 Need to initalize d, low, scc, stacked (see below)

 Output is scc vector, gives each node the index of its connected component (zero based)

 At the end of the run, current_scc has the number of SCCs in the graph


 Complexity: O(E + V)
 d[i] = Discovery time of node i. (Initialize to -1)
 low[i] = Lowest discovery time reachable from node i. 
 scc[i] = Strongly connected component of node i. 
 s = Stack used by the algorithm  stacked[i] = True if i was pushed into s. 
 ticks = Clock used for discovery times (Initialize to 0)
 *current_scc = ID of the current_scc being discovered
 (Initialize to 0)

 */

//vector<vector<int>> g; This is in the general template already
vector<int> d, low, scc;
vector<bool> stacked;
stack<int> s;
int ticks=0, current_scc=0;
void tarjan(int u){
    d[u] = low[u] = ticks++;
    s.push(u);
    stacked[u] = true;
    const vector<int> &out = g[u];
    for (int k=0, m=out.size(); k<m; ++k){
        const int &v = out[k];
        if (d[v] == -1){
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }else if (stacked[v]){
            low[u] = min(low[u], low[v]);
         }
	}
    if (d[u] == low[u]){
        int v;
        do{
            v = s.top();
            s.pop();
            stacked[v] = false;
            scc[v] = current_scc;
        }while (u != v);
        current_scc++;
    }
}

/// Put in main/sol (n is number of vertices)
g=vector<vector<int>>(n+1);
d=vector<int>(n+1);
low=vector<int>(n+1);
scc=vector<int>(n+1);
stacked=vector<bool>(n+1);
for (int i=0;i<=n;i++) {
    d[i]=-1;
}

/// Usage:
for (int i=1; i<=n; i++) { // Important to only start at 1!
    if (d[i]==-1) {
        tarjan(i);
    }
}
