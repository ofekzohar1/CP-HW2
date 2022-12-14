#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

using VI = std::vector<int>;
using VVI = std::vector<VI>;

typedef pair<int, int> pi;
typedef tuple<int, int, int> triple;

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i, start, stop) for (int i = (start); i <= (stop); i++)
#define arrin(a, n) for(int INPUT=0;INPUT<=(n);INPUT++)cin>>a[INPUT]

int q = 2147483647; // 2^31 - 1

/* Key observation - arrowhead for the i-th arrow determine by perm[i]. the free parameter is the base arrow.
 *
 * For the i-th arrow from bottom define:
 *      dp[j] := # of valid signs can build from i-1 arrows s.t the i-1 base is at j.
 *      next_dp[j] := same as above for the i-th arrow.
 *      Base case, dp for 1st arrow: dp[j] = 1 iff j=perm[1], otherwise 0 (only one valid case)
 *      Solution: sum(dp) for the N-th arrow
 *
 * complexity: 3 nested for loops - O(n^3) correspond to fill a dp matrix with O(n) for each element.
 * */
void sol() {
    int N;
    cin >> N;
    VI perm(N + 1);
    arrin(perm, N + 1);
    vector<ll> dp(N + 2), next_dp(N + 2);

    dp[perm[0]] = 1; // 1st arrow base on perm[0]
    REP(i, 2, N) {
        REP (p, 0, i-1) {
            int base = perm[p];
            if (p == i - 1) { // i-1 arrowhead pos == base pos
                if (base < perm[i])
                    // base left to i arrowhead position.
                    // To get valid overlap (i-1) arrow base pos, j, must be right to base+1.
                    REP (j, base + 1, N + 1) {
                        next_dp[base] += dp[j];
                        next_dp[base] %= q;
                    }
                else // base right to i arrowhead position.
                    // To get valid overlap (i-1) arrow base pos, j, must be left to base-1.
                    REP (j, 1, base - 1) {
                        next_dp[base] += dp[j];
                        next_dp[base] %= q;
                    }
            } else if ((base < perm[i] && base < perm[i - 1]) || (base > perm[i] && base > perm[i - 1]))
                // If i-th arrow base is left to i-th,(i-1)-th arrowhead so only right arrow sign is valid
                // Same if i-th is right to them.
                next_dp[base] = dp[base];
        }
        REP(j, 1, N + 1) {
            dp[j] = next_dp[j];
            next_dp[j] = 0;
        }
    }
    ll sol = 0;
    REP(base, 1, N + 1) {
        sol += dp[base]; // sum for the n-th arrow
        sol %= q;
    }
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
