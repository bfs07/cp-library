/// Returns the maximum contiguous sum in the array.
///
/// Time Complexity: O(n)
int kadane(vector<int> &arr) {
  if (arr.empty())
    return 0;
  int sum, tot;
  sum = tot = arr[0];

  for (int i = 1; i < arr.size(); i++) {
    sum = max(arr[i], arr[i] + sum);
    if (sum > tot)
      tot = sum;
  }
  return tot;
}