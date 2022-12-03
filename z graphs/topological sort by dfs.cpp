//  NOTE: you need to allocate space and fill g first!
//  NOTE: we assume indices 1 to n, in input (g) and output (order)!! (1 based index)
/* 
 * Topological sorting by dfs (and cycle detection).
 * - We start dfs from a white node: there's a cycle iff there's a backedge.
 * - We start the order from n-1 to 0. We have the current index
		and for each member we encounter we assign the index to the node and decrease the index.
	 This is equivalent to use the reverse-order encountered in the dfs.
   - We don't care about the order between different dfs trees.
 *
 */
 
 #define WHITE 0
 #define GREY 1
 #define BLACK 2

vector<vector<int>> g; // we assume g is allocated
vector<int> order;
vector<int> color;
int back_edge_spotted = 0;
int p;
void dfs(int v) {
    if(color[v]==GREY) back_edge_spotted = 1;
    if(color[v] != WHITE) return;
    color[v] = GREY;
    for (int neighbor: g[v]) {
        dfs(neighbor);
    }
    color[v] = BLACK;
    order[p] = v; p--;
}

/**
 * Fills order with the order of the topological sort
 * Returns true iff no cycle was found.
 * n is the number of vertices in the graph - assumed to be 1 to n!!!
 */
bool topological_sorting(int n) {
    // init
    color = vector<int>(n+1);
    order = vector<int>(n+1);
    for(int i=1; i<=n; i++) color[i]=WHITE;

    // dfs from each node
    back_edge_spotted=0; p=n;
    for(int i=1; i<=n; i++) {
        if(!color[i]) {
            dfs(i);
            if(back_edge_spotted) {
                return false;
            }
        };
    }
    return true;
}
