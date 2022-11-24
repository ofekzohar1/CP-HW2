/*
 * Topological sorting by dfs.
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
 
int back_edge_spotted = 0, v[..];
int od[..], p; // the final order
void dfs(int a) {
    if(v[a]==GREY) back_edge_spotted = 1;
    if(v[a] != WHITE) return;
    v[a] = GREY;
    for each neighbor a -> i dfs(i);
    v[a] = BLACK;
    od[p] = a; p--;
}
...
for(i=0; i<n; i++) v[i]=0; //white
back_edge_spotted=0; p=n-1;
for(i=0; i<n; i++) if(!v[i])
dfs(i);
if(back_edge_spotted) say there is a cycle;
