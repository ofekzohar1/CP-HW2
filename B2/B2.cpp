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

// A hash function used to hash a tuple & pair
struct hash_tuple {
    size_t operator() (const triple & x)
    const
    {
        return get<0>(x) ^ get<1>(x) ^ get<2>(x);
    }

};
struct hash_pair {

    size_t operator()(const pi& p) const
    {
        auto hash1 = hash<int>{}(p.first);
        auto hash2 = hash<int>{}(p.second);

        if (hash1 != hash2) {
            return hash1 ^ hash2;
        }

        // If hash1 == hash2, their XOR is zero.
        return hash1;
    }
};
typedef unordered_map<triple, int, hash_tuple> DicTriple; // Hash mapping triple -> int
typedef unordered_map<pi, int, hash_pair> DicPair; // Hash mapping pair -> int


VVI g, gFloor; // gFloor - temporary graph holds the floor projection graph
vector<bool> visible;

/** Help function to read the needles into 2 graphs.
 * First one is the 3-dim graph and the 2nd is the projection on XY, allowing repeated edges.
 *
 * @param K # of needles (edges)
 * @return (n,N) # of nodes in g, gFloor
 */
pi readNeedleGraph(int K) {
    // mapping from node's name to its numerical representation
    DicTriple nodes;
    DicPair nodesFloor;

    // Every needle represented by an edge, So max nodes is twice the number of needles = 2K
    g = VVI(2 * K + 1);
    gFloor = VVI(2 * K + 1);
    triple tcord1, tcord2;
    pi pcord1, pcord2;
    int u, v, n = 0, N=0, x,y,z;

    REP(i, 1, K) {
        cin >> x >> y >> z;
        tcord1 = {x,y,z}; pcord1={x,y};
        cin >> x >> y >> z;
        tcord2 = {x,y,z}; pcord2={x,y};

        if (nodes.find(tcord1) == nodes.end()) // nodes.end() == Not founded
            nodes[tcord1] = ++n;
        if (nodes.find(tcord2) == nodes.end())
            nodes[tcord2] = ++n;
        u = nodes[tcord1], v = nodes[tcord2]; // Gets nodes' numerical represent
        // Add new edges to the adj list
        g[u].PB(v);
        g[v].PB(u);

        if (pcord1 == pcord2) continue; // Same node - prevent self loops
        if (nodesFloor.find(pcord1) == nodesFloor.end())
            nodesFloor[pcord1] = ++N;
        if (nodesFloor.find(pcord2) == nodesFloor.end())
            nodesFloor[pcord2] = ++N;
        u = nodesFloor[pcord1], v = nodesFloor[pcord2]; // Gets nodes' numerical represent
        gFloor[u].PB(v);
        gFloor[v].PB(u);
    }
    return {n, N};
}

/** Check if the undirected graph g has a cycle using bfs.
 * If a found an edge (u,v) such v already visited and v didn't discover u == cycle in g
 * We say that u is the parent of v if u discovered v using (u,v).
 *
 * @param n # of nodes in g
 * @return true if cycle was found, otherwise false
 */
bool isCyclic(int n) {
    VI parent(n+1);
    REP(s, 1, n) { // BFS over all nodes in g
        if (!visible[s]) {
            visible[s]=true;
            VI cur_level={s};
            while (!cur_level.empty()) {
                VI next_level;
                for(int u : cur_level) {
                    for(int v : g[u]) {
                        if (!visible[v]) {
                            visible[v] = true;
                            next_level.push_back(v);
                            parent[v] = u;
                        } else if (parent[v] != u && parent[u] != v)
                            // If u,v doesn't share parent relation - there is a cycle
                            return true;
                    }
                }
                cur_level = next_level;
            }
        }
        return false;
    }
}

/** Build graph of the needles coordinates & 2nd graph of the needles cord projection on XY plane.
 * Cycle in either graphs means closed chains (floor or true corresponding to the graph).
 *
 * complexity: 2 DFS to determine if graph is cyclic - O(K);
 */
void sol() {
    int K, n, N; cin >> K;

    pi sz = readNeedleGraph(K);
    n = sz.F, N=sz.S; // # of nodes in g, gFloor
    visible = vector<bool>(n+1, false);
    cout << (isCyclic(n) ? "True closed chains" : "No true closed chains") << "\n";

    g = gFloor;
    visible = vector<bool>(N+1, false);
    cout << (isCyclic(N) ? "Floor closed chains" : "No floor closed chains") << "\n";
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
