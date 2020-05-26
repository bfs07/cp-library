// |A ∪ B ∪ C|=|A|+|B|+|C|-|A ∩ B|-|A ∩ C|-|B ∩ C|+|A ∩ B ∩ C|
// EXAMPLE: How many numbers from 1 to 10^9 are multiple of 42, 54, 137 or 201?
int f(const vector<int> &arr, const int LIMIT) {
  int n = arr.size();
  int c = 0;

  for (int mask = 1; mask < (1ll << n); mask++) {
    int lcm = 1;
    for (int i = 0; i < n; i++)
      if (mask & (1ll << i))
        lcm = lcm * arr[i] / __gcd(lcm, arr[i]);
    // if the number of element is odd, then add
    if (__builtin_popcount_ll(mask) % 2 == 1)
      c += LIMIT / lcm;
    else // otherwise subtract
      c -= LIMIT / lcm;
  }

  return LIMIT - c;
}
