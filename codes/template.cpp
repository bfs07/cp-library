#include <bits/stdc++.h>

using namespace std;

#define eb emplace_back
#define ii pair<int, int>
#define OK (cerr << "OK" << endl)
#define debug(x) cerr << #x " = " << (x) << endl
#define ff first
#define ss second
#define int long long
#define tt tuple<int, int, int>
#define all(x) x.begin(), x.end()
#define vi vector<int>
#define vii vector<pair<int, int>>
#define vvi vector<vector<int>>
#define vvii vector<vector<pair<int, int>>>
#define Mat(n, m, v) vector<vector<int>>(n, vector<int>(m, v))
#define endl '\n'

constexpr int INF = (sizeof(int) == 4 ? 1e9 : 2e18) + 1e5;
constexpr int MOD = 1e9 + 7;
constexpr int MAXN = 2e5 + 3;

#define MULTIPLE_TEST_CASES
void solve(const int test) {
  int n;
  cin >> n;
}

signed main() {
  // const string FILE_NAME = "";
  // freopen((FILE_NAME + string(".in")).c_str(), "r", stdin);
  // freopen((FILE_NAME + string(".out")).c_str(), "w", stdout);
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  int t = 1;
#ifdef MULTIPLE_TEST_CASES
  cin >> t;
#endif
  for (int i = 1; i <= t; ++i)
    solve(i);
}
