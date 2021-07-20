void subsetSum(const vector<int> &arr) {
  bitset<312345> bit;
  bit.set(0);
  for (int i = 0; i < arr.size(); i++)
    bit |= bit << arr[i];
}