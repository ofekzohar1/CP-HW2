#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

using VI = std::vector<int>;
using VVI = std::vector<VI>;

typedef pair<int,int> pi;
typedef tuple<int, int, int> triple;

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i, start, stop) for (int i = (start); i <= (stop); i++)
#define arrin(a,n) for(int INPUT=0;INPUT<n;INPUT++)cin>>a[INPUT]


vector<vector<int>> g; vector<bool> visible;

/*********** Topo Sort *****************/

#define WHITE 0
#define GREY 1
#define BLACK 2

VI order; // Contain topological order
VI color; // Colors array for dfs
int back_edge_spotted = 0;
int p;

// DFS implementation
void dfs(int v) {
    if (color[v] == GREY) back_edge_spotted = 1;
    if (color[v] != WHITE) return;
    color[v] = GREY;
    for (int neighbor: g[v]) {
        dfs(neighbor);
    }
    color[v] = BLACK;
    order[p] = v;
    p--;
}

/**
 * Fills order with the order of the topological sort
 * Returns true iff no cycle was found.
 * n is the number of vertices in the graph - assumed to be 1 to n!!!
 */
bool topological_sorting(int n) {
    // init
    color = vector<int>(n + 1);
    order = vector<int>(n + 1);
    for (int i = 1; i <= n; i++) color[i] = WHITE;

    // dfs from each node
    back_edge_spotted = 0;
    p = n;
    for (int i = 1; i <= n; i++) {
        if (!color[i]) {
            dfs(i);
            if (back_edge_spotted) {
                return false;
            }
        };
    }
    return true;
}

void create_and_parse_directed_graph(int n, int m, vector<bool>& inDegZero) {
    g = VVI(n+1);
    REP(i,1,m) {
        int a_i, b_i; cin >> a_i >> b_i;
        g[a_i+1].push_back(b_i+1);
        inDegZero[b_i+1] = false; // edge (a_i,b_i) exist so b_i's indegree >= 1
    }
}

VI longest_paths_in_dag(int n) {
    VI dist(n + 1);
    int u;
    REP(i,0,n) {
        u = order[i];
        for (int v : g[u]) {
            if (dist[v] < dist[u] + 1)
                dist[v] = dist[u] + 1;
        }
    }
    return dist;
}

void sol() {
    int A, B, E, P;
    cin >> A >> B >> E >> P;
    vector<bool> inDegZero = vector<bool>(E+1, true); //boolean array whose every node with indegree zero gets true
    create_and_parse_directed_graph(E, P, inDegZero);

    REP(i, 1, E) { // Connect '0' node to all source nodes (nodes with indegree 0)
        if (inDegZero[i])
            g[0].push_back(i);
    }
    topological_sorting(E);
    VI nodes_layers_map = longest_paths_in_dag(E);

    int max_layer = *max_element(nodes_layers_map.begin(), nodes_layers_map.end());
    VI num_of_nodes_by_layer(max_layer + 1);
    REP(i,1,E) num_of_nodes_by_layer[nodes_layers_map[i]]++;
    int cnt = 0, next_cnt;
    bool A_res_printed = false, B_res_printed = false;
    REP(i,1,max_layer) {
        next_cnt = cnt + num_of_nodes_by_layer[i];
        if (!A_res_printed && next_cnt >= A) {
            cout << (next_cnt == A ? A : cnt) << "\n";
            A_res_printed = true;
        }
        if (next_cnt >= B) {
            cout << (next_cnt == B ? B : cnt) << "\n";
            cout << E-next_cnt << "\n";
            break;
        }
        cnt = next_cnt;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
#ifndef ONLINE_JUDGE

    // For getting input from input.txt file
    freopen("input.txt", "r", stdin);

    // Printing the Output to output.txt file
    freopen("output.txt", "w", stdout);

#endif
        sol();
    return 0;
}
