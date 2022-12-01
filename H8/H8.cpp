#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <iomanip>
#include <cmath>
#include <stack>
#include <climits>

using namespace std;
typedef long long ll;

using VI = std::vector<int>;
using VVI = std::vector<VI>;

typedef pair<int,int> pi;

#define F first
#define S second
#define PB push_back
#define MP make_pair

#define arrin(a,n) for(int INPUT=0;INPUT<n;INPUT++)cin>>a[INPUT]


vector<vector<int>> g; vector<bool> visible;
vector<vector<int>> children;

int q = 1000000007;

void sol() {

}

int main() {
    ios_base::sync_with_stdio(false);
#ifndef ONLINE_JUDGE

    // For getting input from input.txt file
    freopen("input.txt", "r", stdin);

    // Printing the Output to output.txt file
    freopen("output.txt", "w", stdout);

#endif
    int t; cin >> t;
    while (t--) {
        sol();
    }
    return 0;
}
