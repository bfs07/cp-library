/// Time Complexity: O(n)
int largest_area_in_histogram(vector<int> &arr) {
  arr.eb(0);

  stack<int> s;
  int ans = 0;
  for (int i = 0; i < arr.size(); ++i) {
    while (!s.empty() && arr[s.top()] >= arr[i]) {
      int height = arr[s.top()];
      s.pop();
      int l = (s.empty() ? 0 : s.top() + 1);
      // creates a rectangle from l to i - 1
      ans = max(ans, height * (i - l));
    }
    s.emplace(i);
  }
  return ans;
}
