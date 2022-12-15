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

#define arrin(a,n) for(int INPUT=1;INPUT<=n;INPUT++)cin>>a[INPUT]


VVI g;
vector<ll> sum_cit, sum_leaf;

void dfs(int u, ll &sol) {
    sum_leaf[u] = g[u].empty() ? 1 : 0; // g[u].empty() true == u is a leaf
    for (auto v : g[u]) {
        dfs(v, sol); // Apply DFS rec
        sum_cit[u] += sum_cit[v]; // Sum all subtree
        sum_leaf[u] += sum_leaf[v];
    }
    if (sum_cit[u] % sum_leaf[u] == 0)
        sol = max(sol, sum_cit[u] / sum_leaf[u]);
    else // People cannot be divided, so we need to add 1 to the maximum
        sol = max(sol, sum_cit[u] / sum_leaf[u] + 1);
}

void create_and_parse_directed_graph(int n, int m) {
    g = VVI(n+1);
    for (int i = 1; i <= m; i++) {
        int p_i; cin >> p_i;
        g[p_i].PB(i+1);
    }
}

/** Key observation - we want that the # of citizens on each leaf would be the same.
 *  The city graph i a directed tree so we could define the subtree rooted at u.
 *  we want for any subtree to distribute the citizens equally among the leafs.
 *
 *  We use the Recursice property of the DFS to calculate for each subtree (say rooted at u):
 *      sum_cit[u] := # of citizens in the subtree
 *      sum_leaf[u] := # of leafs in the subtree
 * Goal - sum_cit[u] / sum_leaf[u] (+1)
 * SOl - max_u{sum_cit[u] / sum_leaf[u]}
 *
 * complexity: DFS - O(n).
 */
void sol() {
    int n; cin >> n;
    sum_cit = vector<ll>(n+1);
    sum_leaf = vector<ll>(n+1);

    create_and_parse_directed_graph(n, n-1);
    arrin(sum_cit,n);

    ll sol = 0;
    dfs(1, sol);
    cout << sol << "\n";
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
