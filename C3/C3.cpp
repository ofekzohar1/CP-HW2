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

VVI g, g_transpose; // G^T - same nodes, edges change direction
vector<bool> visible;

void create_and_parse_directed_graph(int n, int m) {
    g = VVI(n+1);
    g_transpose = VVI(n+1);
    REP(i,1,m) {
        int a_i, b_i; cin >> a_i >> b_i;
        g[a_i+1].push_back(b_i+1);
        g_transpose[b_i+1].push_back(a_i+1);
    }
}

/** Calculate x's # of descendants using BFS
 *
 * @param graph The graph
 * @param x source node
 * @param n # of nodes in the graph
 * @return x's # of descendants
 */
int bfs_cnt_descendants(VVI& graph ,int x, int n) {
    REP(i,1,n) visible[i] = false;
    visible[x]=true;
    vector<int> cur_level={x};
    int cnt_descendants = 1;
    while (!cur_level.empty()) {
        vector<int> next_level;
        for(int f : cur_level) {
            for(int s : graph[f]) {
                if (visible[s]) continue;
                visible[s]=true;
                next_level.push_back(s);
                cnt_descendants++;
            }
        }
        cur_level = next_level;
    }
    return cnt_descendants;
}

/**
 * Key Observation #1: for a fixed node u, all u's descendants (u outperform those) cannot be promoted unless
 * u is promoted. All other nodes can/cannot be promoted regardless of u's promotion (they dont share performance relation)
 * So u won't be promoted iff we have enough emp to promote without u and his descendents.
 * We can use BFS to determine # of des for each node.
 *
 * Key Observation #2: for a fixed node u, all u's ancestors (those outperform u) must be promoted before u.
 * If u's # of ans' is bigger than B so u will never be promoted!
 * We can use BFS on the transposed graph to determine # of ans' for each node.
 *
 * complexity: O(|V|(|V|+|E|))=O(E*P+E^2), 2 bfs for each node.
 */
void sol() {
    int A, B, E, P;
    cin >> A >> B >> E >> P;
    create_and_parse_directed_graph(E, P);

    int A_must_prom = 0, B_must_prom = 0, B_never_prom = 0, u_des, u_ans;
    visible = vector<bool>(E+1);
    REP(u,1,E) {
        u_des = bfs_cnt_descendants(g, u, E);
        A_must_prom += E - u_des < A ? 1 : 0; // if E - u_des < A so we can promote at least another emp, promote u
        B_must_prom += E - u_des < B ? 1 : 0; // Same as above

        u_ans = bfs_cnt_descendants(g_transpose, u, E); // u's descendant in G^T is an ancestor in G
        B_never_prom += u_ans > B ? 1 : 0; // We must promote all u's ans' before u but they are more than B!
    }

    cout << A_must_prom << "\n" << B_must_prom << "\n" << B_never_prom;
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
