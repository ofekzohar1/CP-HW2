#include <bits/stdc++.h>

using namespace std;

using VI = vector<int>;
typedef pair<int, int> pi;

struct edge { // Edge struct contain To's node, cost and prestige of the edge
    int to, cost, pres;
} typedef EDGE;

#define COST first
#define PRES second
#define PB push_back
#define MP make_pair
#define REP(i, start, stop) for (int i = (start); i <= (stop); i++)

vector<vector<EDGE>> g;
const int maxCost = 10001; // constant for max cost

/*********** Topo Sort *****************/

#define WHITE 0
#define GREY 1
#define BLACK 2

VI order; // Contain topological order
VI color; // Colors array for dfs
int back_edge_spotted = 0;
int p;

// DFS implementation using EDGE struct
void dfs(int v) {
    if (color[v] == GREY) back_edge_spotted = 1;
    if (color[v] != WHITE) return;
    color[v] = GREY;
    for (EDGE neighbor: g[v]) {
        dfs(neighbor.to);
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

/*********** Help Functions *****************/

/** Help function to read the dish receipts into a graph
 *
 * @param nodes mapping from node's name to its numerical representation
 * @param N # of edges
 * @param inDegZero boolean array whose every node with indegree zero gets true
 *                  the algorithm fill the array with the correct value
 * @return # of nodes in the graph
 */
int readDishGraph(unordered_map<string, int> &nodes, int N, vector<bool> &inDegZero) {
    // Every recipe  has base dish and derived dish
    // So max nodes is twice the number of recipes = 2N
    g = vector<vector<EDGE>>(2 * N + 1);
    string derDish, baseDish, ing;
    int u, v, cost, pres, n = 0;

    REP(i, 1, N) {
        cin >> derDish >> baseDish >> ing >> cost >> pres;
        // If der/base dish doesn't exist yet has a node in the graph
        // Assign the next free numerical node into dish's mapping
        if (nodes.find(baseDish) == nodes.end()) // nodes.end() == Not founded
            nodes[baseDish] = ++n;
        if (nodes.find(derDish) == nodes.end())
            nodes[derDish] = ++n;
        u = nodes[baseDish], v = nodes[derDish]; // Gets nodes' numerical represent
        g[u].PB({v, cost, pres}); // Add new edge to the adj list
        inDegZero[v] = false; // edge (u,v) exist so v's indegree >= 1
    }
    return n;
}

/** Calc shortest "path" from any base dish to any derived dish according to minimal cost
 * If exist 2 path's with same cost, choose the one maximize the prestige.
 * To get through all the nodes we use new source node '0' who connected
 *      to all nodes with indegree zero.
 *
 * @param minCmaxP Array contain the min cost and max prestige correspond to the shortest path
 *                 for each node. Filled during the algorithm
 * @param n # of nodes
 */
void shortestPathTopoSort(vector<pi> &minCmaxP, int n) {
    int u, v;
    minCmaxP[0].COST = 0; // 0 cost for the source
    REP(i, 0, n) {
        u = order[i]; // Iterate the nodes in the topo order
        for (auto edge: g[u]) {
            v = edge.to;
            // IF v's cuur cost > u's curr cost + cost(u,v), update to the better "path"
            if (minCmaxP[v].COST > edge.cost + minCmaxP[u].COST) {
                minCmaxP[v].COST = edge.cost + minCmaxP[u].COST;
                minCmaxP[v].PRES = edge.pres + minCmaxP[u].PRES;
                // IF v's cuur cost = u's curr cost + cost(u,v), update only if the new "path" has better prestige
            } else if (minCmaxP[v].COST == edge.cost + minCmaxP[u].COST &&
                       minCmaxP[v].PRES < edge.pres + minCmaxP[u].PRES) {
                minCmaxP[v].PRES = edge.pres + minCmaxP[u].PRES;
            }
        }
    }
}

/*********** Solution *****************/

void sol() {
    int B, N;
    cin >> B >> N;
    VI dp = VI(B + 1);
    unordered_map<string, int> nodes; // mapping from node's name to its numerical representation
    vector<bool> inDegZero = vector<bool>(2 * N + 1,
                                          true); //boolean array whose every node with indegree zero gets true

    int n = readDishGraph(nodes, N, inDegZero); // n = # of nodes
    REP(i, 1, n) { // Connect '0' node to all source nodes (nodes with indegree 0)
        if (inDegZero[i])
            g[0].push_back({i, 0, 0}); // Cost & Pres are zero
    }
    topological_sorting(n);
    vector<pi> minCmaxP = vector<pi>(n + 1, {maxCost, 0});
    shortestPathTopoSort(minCmaxP, n); // Calc the shortest "path" to each dish using the topo sort

    /* dp[i] := The maximum prestige we can get using i euros. 0<=i<=B.
     * dp[0] = 0, maxi{dp[i]}
     * max prestige = maxi{dp[i]}, min cost for that prestige = argmax.
     * Iterate over the dishes and update dp[i] if the dish can be afforded (i>=cost)
     *      & adding the dish prestige to dp[i-cost] is better than curr prestige.
     * For each dish iterate only on the affordable budgets from the end
     *      so the dish won't count twice
     * */
    REP(u, 1, n) {
        for (int b = B; b >= minCmaxP[u].COST; b--)
            dp[b] = max(dp[b], dp[b - minCmaxP[u].COST] + minCmaxP[u].PRES);
    }
    int minCost = 0, maxPres = 0;
    REP(b, 0, B) {
        if (dp[b] > maxPres) {
            maxPres = dp[b];
            minCost = b;
        }
    }
    cout << maxPres << "\n" << minCost << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE

    // For getting input from input.txt file
    freopen("input.txt", "r", stdin);

    // Printing the Output to output.txt file
    freopen("output.txt", "w", stdout);

#endif
    sol();
}
