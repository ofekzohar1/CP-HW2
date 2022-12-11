#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;

using VI = vector<int>;
typedef pair<int, int> pi;

struct edge {
    int to, cost, pres;
} typedef EDGE;

#define COST first
#define PRES second
#define PB push_back
#define MP make_pair
#define REP(i, start, stop) for (int i = (start); i <= (stop); i++)

vector<vector<EDGE>> g;
int maxCost = 10001;

/*********** Topo Sort *****************/

#define WHITE 0
#define GREY 1
#define BLACK 2

vector<int> order;
vector<int> color;
int back_edge_spotted = 0;
int p;

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

int readDishGraph(unordered_map<string, int> &nodes, int N, vector<bool> &inDegZero) {
    g = vector<vector<EDGE>>(2 * N + 1);
    string derDish, baseDish, ing;
    int u, v, cost, pres, n = 0;

    REP(i, 1, N) {
        cin >> derDish >> baseDish >> ing >> cost >> pres;
        if (nodes.find(baseDish) == nodes.end())
            nodes[baseDish] = ++n;
        if (nodes.find(derDish) == nodes.end())
            nodes[derDish] = ++n;
        u = nodes[baseDish], v = nodes[derDish];
        EDGE edge_uv = {v, cost, pres};
        g[u].PB(edge_uv);
        inDegZero[v] = false;
    }
    return n;
}

void shortestPathTopoSort(vector<pi> &minCmaxP, int n) {
    int u, v;
    minCmaxP[0].COST = 0;
    REP(i, 0, n) {
        u = order[i];
        for (auto edge: g[u]) {
            v = edge.to;
            if (minCmaxP[v].COST > edge.cost + minCmaxP[u].COST) {
                minCmaxP[v].COST = edge.cost + minCmaxP[u].COST;
                minCmaxP[v].PRES = edge.pres + minCmaxP[u].PRES;
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
    unordered_map<string, int> nodes;
    vector<bool> inDegZero = vector<bool>(2 * N + 1, true);

    int n = readDishGraph(nodes, N, inDegZero);
    REP(i, 1, n) {
        if (inDegZero[i])
            g[0].push_back({i, 0, 0});
    }
    topological_sorting(n);
    vector<pi> minCmaxP = vector<pi>(n + 1, {maxCost, 0});
    shortestPathTopoSort(minCmaxP, n);

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
#ifndef ONLINE_JUDGE

    // For getting input from input.txt file
    freopen("input.txt", "r", stdin);

    // Printing the Output to output.txt file
    freopen("output.txt", "w", stdout);

#endif
    sol();
}
