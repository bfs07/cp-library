set<pair<int, int>> s[(int)2e6];
bool check(pair<int, int> par, int ind) {
  auto it = s[ind].lower_bound(pair<int, int>(par.ff, -INF));
  if (it == s[ind].begin())
    return false;
  it--;
  if (it->ss < par.ss)
    return true;
  return false;
}

int lis2d(vector<pair<int, int>> &arr) {
  const int n = arr.size();
  s[1].insert(arr[0]);

  int maior = 1;
  for (int i = 1; i < n; i++) {
    pair<int, int> x = arr[i];
    int l = 1, r = maior;
    int ansbb = 0;
    while (l <= r) {
      int mid = (l + r) / 2;
      if (check(x, mid)) {
        l = mid + 1;
        ansbb = mid;
      } else {
        r = mid - 1;
      }
    }

    // inserting in list
    auto it = s[ansbb + 1].lower_bound(pair<int, int>(x.ff, -INF));
    while (it != s[ansbb + 1].end() && it->ss >= x.ss)
      it = s[ansbb + 1].erase(it);

    it = s[ansbb + 1].lower_bound(pair<int, int>(x.ff, -INF));
    if (s[ansbb + 1].size() > 0 && it != s[ansbb + 1].end() && it->ff == x.ff &&
        it->ss <= x.ss)
      continue;
    s[ansbb + 1].insert(arr[i]);

    maior = max(maior, ansbb + 1);
  }

  return maior;
}