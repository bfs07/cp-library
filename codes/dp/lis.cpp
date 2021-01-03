int lis(vector<int> &arr) {
  int n = arr.size();
  vector<int> lis;
  for (int i = 0; i < n; i++) {
    int l = 0, r = (int)lis.size() - 1;
    int ansj = -1;
    while (l <= r) {
      int mid = (l + r) / 2;
      // OBS: - To >= LIS change to the operation below to >
      //      - Put <= or >= for strictly!!
      if (arr[i] < lis[mid]) {
        r = mid - 1;
        ansj = mid;
      } else
        l = mid + 1;
    }
    if (ansj == -1)
      lis.emplace_back(arr[i]);
    else
      lis[ansj] = arr[i];
  }

  return lis.size();
}
