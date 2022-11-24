
/*
 *
 Tarjan's algorithm for finding strongly connected components (SCC)
 
 Complexity: O(E + V)
 d[i] = Discovery time of node i. (Initialize to -1)
 low[i] = Lowest discovery time reachable from node i. 
 scc[i] = Strongly connected component of node i. 
 s = Stack used by the algorithm  stacked[i] = True if i was pushed into s. 
 ticks = Clock used for discovery times (Initialize to 0)
 *current_scc = ID of the current_scc being discovered
 (Initialize to 0)
 
 
 Some analysis:
  - DFS gives us a forest of connected trees
  - SCCs are subtrees of DFS trees.
  - The head of a subtree which is a SCC can be the representative of the SCC.
  - There is no back-edge and no cross-edge from one SCC to another.
	* (If there is a back-edge -> same SCC)
	* (There might be a cross edge but it will not be used (need more info on this maybe))
  - 
 
 */

vector<int> g[MAXN];
int d[MAXN], low[MAXN], scc[MAXN];
bool stacked[MAXN];
stack<int> s;
int ticks, current_scc;
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

