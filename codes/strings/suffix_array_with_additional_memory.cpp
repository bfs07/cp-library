namespace RadixSort {
/// Sorts the array arr stably in ascending order.
///
/// Time Complexity: O(n + max_element)
/// Space Complexity: O(n + max_element)
template <typename T>
void sort(vector<T> &arr, const int max_element, int (*get_key)(T &),
          int begin = 0) {
  const int n = arr.size();
  vector<T> new_order(n);
  vector<int> count(max_element + 1, 0);

  for (int i = begin; i < n; i++)
    count[get_key(arr[i])]++;

  for (int i = 1; i <= max_element; i++)
    count[i] += count[i - 1];

  for (int i = n - 1; i >= begin; i--) {
    new_order[count[get_key(arr[i])]] = arr[i];
    count[get_key(arr[i])]--;
  }

  arr = new_order;
}

/// Sorts an array by their pair of ranks stably in ascending order.
template <typename T> void sort_pairs(vector<T> &arr, const int rank_size) {
  // Sort by the second rank
  RadixSort::sort<T>(
      arr, rank_size, [](T &item) { return item.first.second; }, 1ll);

  // Sort by the first rank
  RadixSort::sort<T>(
      arr, rank_size, [](T &item) { return item.first.first; }, 1ll);
}
} // namespace RadixSort

/// It is indexed by 1.
class Suffix_Array {
private:
  string s;
  int n;

  typedef pair<int, int> Rank;
  vector<int> suffix_array;
  vector<int> lcp;

  vector<vector<int>> rank_table;
  vector<int> log_array;

public:
  Suffix_Array(const string &s) {
    this->n = s.size();
    this->s = "#" + s;

    build_log_array();
    build_suffix_array();
    lcp = build_lcp();
  }

private:
  vector<int> build_ranks(const vector<pair<Rank, int>> &ranks) {
    vector<int> arr(this->n + 1);

    arr[ranks[1].second] = 1;
    for (int i = 2; i <= n; i++) {
      // If their rank are equal, than its position should be the same.
      if (ranks[i - 1].first == ranks[i].first)
        arr[ranks[i].second] = arr[ranks[i - 1].second];
      else
        arr[ranks[i].second] = arr[ranks[i - 1].second] + 1;
    }

    return arr;
  }

  /// Builds the Suffix Array for the string s.
  ///
  /// Time Complexity: O(n*log(n))
  /// Space Complexity: O(n*log(n))
  void build_suffix_array() {
    // This tuple below represents the rank and the index associated with it.
    vector<pair<Rank, int>> ranks(this->n + 1);
    vector<int> arr;

    int rank_table_size = 0;
    this->rank_table.resize(log_array[this->n] + 2);

    for (int i = 1; i <= this->n; i++)
      ranks[i] = pair<Rank, int>(Rank(s[i], 0), i);

    // Inserting only the ranks in the table.
    transform(ranks.begin(), ranks.end(),
              back_inserter(rank_table[rank_table_size++]),
              [](pair<Rank, int> &pair) { return pair.first.first; });

    RadixSort::sort_pairs(ranks, 256);
    arr = build_ranks(ranks);

    {
      int jump = 1;
      int max_rank = arr[ranks.back().second];

      // It will be compared intervals a pair of intervals (i, jump-1), (i +
      // jump, i + 2*jump - 1). The variable jump is always a power of 2.
      while (jump < n) {
        for (int i = 1; i <= this->n; i++) {
          ranks[i].first.first = arr[i];
          ranks[i].first.second = (i + jump <= this->n ? arr[i + jump] : 0);
          ranks[i].second = i;
        }

        // Inserting only the ranks in the table.
        transform(ranks.begin(), ranks.end(),
                  back_inserter(rank_table[rank_table_size++]),
                  [](pair<Rank, int> &pair) { return pair.first.first; });

        RadixSort::sort_pairs(ranks, n);

        arr = build_ranks(ranks);

        max_rank = arr[ranks.back().second];
        jump *= 2;
      }

      for (int i = 1; i <= n; i++) {
        ranks[i].first.first = arr[i];
        ranks[i].first.second = (i + jump <= this->n ? arr[i + jump] : 0);
        ranks[i].second = i;
      }

      // Inserting only the ranks in the table.
      transform(ranks.begin(), ranks.end(),
                back_inserter(rank_table[rank_table_size++]),
                [](pair<Rank, int> &pair) { return pair.first.first; });
    }

    this->suffix_array.resize(this->n + 1);
    for (int i = 1; i <= this->n; i++)
      this->suffix_array[arr[i]] = i;
  }

  /// Builds the lcp (Longest Common Prefix) array for the string s.
  /// A value lcp[i] indicates length of the longest common prefix of the
  /// suffixes indexed by i and i + 1. Implementation of the Kasai's Algorithm.
  ///
  /// Time Complexity: O(n)
  /// Space Complexity: O(n)
  vector<int> build_lcp() {
    vector<int> lcp(this->n + 1, 0);
    vector<int> inverse_suffix(this->n + 1, 0);

    for (int i = 1; i <= n; i++)
      inverse_suffix[suffix_array[i]] = i;

    int k = 0;

    for (int i = 1; i <= n; i++) {
      if (inverse_suffix[i] == n) {
        k = 0;
        continue;
      }

      int j = suffix_array[inverse_suffix[i] + 1];

      while (i + k <= this->n && j + k <= this->n && s[i + k] == s[j + k])
        k++;

      lcp[inverse_suffix[i]] = k;

      if (k > 0)
        k--;
    }

    return lcp;
  }

  void build_log_array() {
    log_array.resize(this->n + 1, 0);

    for (int i = 2; i <= this->n; i++)
      log_array[i] = log_array[i / 2] + 1;
  }

public:
  const vector<int> &get_suffix_array() { return suffix_array; }

  const vector<int> &get_lcp() { return lcp; }

  /// LCS of two strings A and B.
  ///
  /// The string s must be initialized in the constructor as the string (A + '$'
  /// + B).
  ///
  /// The string A starts at index 1 and ends at index (separator - 1).
  /// The string B starts at index (separator + 1) and ends at the end of the
  /// string.
  ///
  /// Time Complexity: O(n)
  /// Space Complexity: O(1)
  int lcs(int separator) {
    separator++;
    assert(!isalpha(this->s[separator] && !isdigit(this->s[separator])));

    int ans = 0;

    for (int i = 1; i < this->n - 1; i++) {
      int left = this->suffix_array[i];
      int right = this->suffix_array[i + 1];

      if ((left < separator && right > separator) ||
          (left > separator && right < separator))
        ans = max(ans, lcp[i]);
    }

    return ans;
  }

  /// Compares two substrings beginning at indexes i and j of a fixed length.
  ///
  /// OBS: Necessary build rank_table (uncomment build_suffix_array) and build
  /// log_array.
  ///
  /// Time Complexity: O(1)
  /// Space Complexity: O(1)
  int compare(const int i, const int j, const int length) {
    assert(1 <= i && i <= this->n && 1 <= j && j <= this->n);
    assert(!this->log_array.empty() && !this->rank_table.empty());
    assert(i + length - 1 <= this->n && j + length - 1 <= this->n);

    // Greatest k such that 2^k <= l
    const int k = this->log_array[length];

    const int jump = length - (1 << k);

    const pair<int, int> iRank = {
        this->rank_table[k][i],
        (i + jump <= this->n ? this->rank_table[k][i + jump] : -1)};
    const pair<int, int> jRank = {
        this->rank_table[k][j],
        (j + jump <= this->n ? this->rank_table[k][j + jump] : -1)};

    return iRank == jRank ? 0 : iRank < jRank ? -1 : 1;
  }
};
