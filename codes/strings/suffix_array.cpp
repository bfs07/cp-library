// To use the compare method use the macro below.
// #define BUILD_TABLE

namespace RadixSort {
/// Sorts the array arr stably in ascending order.
///
/// Time Complexity: O(n + max_element)
/// Space Complexity: O(n + max_element)
template <typename T>
void sort(vector<T> &arr, const int max_element, int (*get_key)(T &),
          const int begin = 0) {
  const int n = arr.size();
  vector<T> new_order(n);
  vector<int> count(max_element + 1, 0);

  for (int i = begin; i < n; ++i)
    ++count[get_key(arr[i])];

  for (int i = 1; i <= max_element; ++i)
    count[i] += count[i - 1];

  for (int i = n - 1; i >= begin; --i) {
    new_order[count[get_key(arr[i])] - (begin == 0)] = arr[i];
    --count[get_key(arr[i])];
  }

  arr = move(new_order);
}

/// Sorts an array by their pair of ranks stably in ascending order.
template <typename T> void sort_pairs(vector<T> &arr, const int rank_size) {
  // sort by the second rank
  RadixSort::sort<T>(
      arr, rank_size, [](T &item) { return item.first.second; }, 0);

  // sort by the first rank
  RadixSort::sort<T>(
      arr, rank_size, [](T &item) { return item.first.first; }, 0);
}
} // namespace RadixSort

// clang-format off
/// It is indexed by 0.
/// Let the given string be "banana".
///
/// 0 banana                          5 a
/// 1 anana     Sort the Suffixes     3 ana
/// 2 nana      ---------------->     1 anana
/// 3 ana        alphabetically       0 banana
/// 4 na                              4 na
/// 5 a                               2 nana
/// So the suffix array for "banana" is {5, 3, 1, 0, 4, 2}
///
/// LCP
/// 1 a
/// 3 ana
/// 0 anana
/// 0 banana
/// 2 na
/// 0 nana (The last position will always be zero)
/// So the LCP for "banana" is {1, 3, 0, 0, 2, 0}
class Suffix_Array {
private:
  const string s;
  const int n;

  typedef pair<int, int> Rank;

  #ifdef BUILD_TABLE
  vector<vector<int>> rank_table;
  const vector<int> log_array = build_log_array();
  #endif
public:
  Suffix_Array(const string &s) : n(s.size()), s(s) {}

private:
  vector<int> build_log_array() {
    vector<int> log_array(this->n + 1, 0);
    for (int i = 2; i <= this->n; ++i)
      log_array[i] = log_array[i / 2] + 1;
    return log_array;
  }

  static void build_ranks(const vector<pair<Rank, int>> &ranks,
                          vector<int> &ret) {
    // The vector containing the ranks will be present at ret
    ret[ranks[0].second] = 1;
    for (int i = 1; i < ranks.size(); ++i) {
      // if their rank are equal, than their position should be the same
      if (ranks[i - 1].first == ranks[i].first)
        ret[ranks[i].second] = ret[ranks[i - 1].second];
      else
        ret[ranks[i].second] = ret[ranks[i - 1].second] + 1;
    }
  }

  /// Time Complexity: O(n*log(n))
  vector<int> build_suffix_array() {
    // the tuple below represents the rank and the index associated with it
    vector<pair<Rank, int>> ranks(this->n);
    vector<int> arr(this->n);

    for (int i = 0; i < n; ++i)
      ranks[i] = pair<Rank, int>(Rank(s[i], 0), i);

    #ifdef BUILD_TABLE
    int rank_table_size = 0;
    this->rank_table.resize(log_array[this->n] + 2);
    #endif
    RadixSort::sort_pairs(ranks, 256);
    build_ranks(ranks, arr);

    {
      int jump = 1;
      int max_rank = arr[ranks.back().second];

      // it will be compared intervals a pair of intervals (i, jump-1), (i +
      // jump, i + 2*jump - 1). The variable jump is always a power of 2
      #ifdef BUILD_TABLE
      while (jump / 2 < this->n) {
      #else
      while (max_rank != this->n) {
      #endif
        for (int i = 0; i < this->n; ++i) {
          ranks[i].first.first = arr[i];
          ranks[i].first.second = (i + jump < this->n ? arr[i + jump] : 0);
          ranks[i].second = i;
        }

        #ifdef BUILD_TABLE
        // inserting only the ranks in the table
        transform(ranks.begin(), ranks.end(),
                  back_inserter(rank_table[rank_table_size++]),
                  [](pair<Rank, int> &pair) { return pair.first.first; });
        #endif
        RadixSort::sort_pairs(ranks, n);
        build_ranks(ranks, arr);

        max_rank = arr[ranks.back().second];
        jump *= 2;
      }
    }

    vector<int> sa(this->n);
    for (int i = 0; i < this->n; ++i)
      sa[arr[i] - 1] = i;
    return sa;
  }

  /// Builds the lcp (Longest Common Prefix) array for the string s.
  /// A value lcp[i] indicates length of the longest common prefix of the
  /// suffixes indexed by i and i + 1. Implementation of the Kasai's Algorithm.
  ///
  /// Time Complexity: O(n)
  vector<int> build_lcp() {
    vector<int> lcp(this->n, 0);
    vector<int> inverse_suffix(this->n);

    for (int i = 0; i < this->n; ++i)
      inverse_suffix[sa[i]] = i;

    for (int i = 0, k = 0; i < this->n; ++i) {
      if (inverse_suffix[i] == this->n - 1) {
        k = 0;
      } else {
        int j = sa[inverse_suffix[i] + 1];
        while (i + k < this->n && j + k < this->n && s[i + k] == s[j + k])
          ++k;

        lcp[inverse_suffix[i]] = k;

        if (k > 0)
          --k;
      }
    }

    return lcp;
  }

  int _lcs(const int separator) {
    int ans = 0;
    for (int i = 0; i + 1 < this->sa.size(); ++i) {
      const int left = this->sa[i];
      const int right = this->sa[i + 1];
      if ((left < separator && right > separator) ||
          (left > separator && right < separator))
        ans = max(ans, lcp[i]);
    }
    return ans;
  }

  #ifdef BUILD_TABLE
  int _compare(const int i, const int j, const int length) {
    const int k = this->log_array[length]; // floor log2(length)
    const int jump = length - (1ll << k);

    const pair<int, int> iRank = {
        this->rank_table[k][i],
        (i + jump < this->n ? this->rank_table[k][i + jump] : -1)};
    const pair<int, int> jRank = {
        this->rank_table[k][j],
        (j + jump < this->n ? this->rank_table[k][j + jump] : -1)};
    return iRank == jRank ? 0 : iRank < jRank ? -1 : 1;
  }
  #endif

public:
  const vector<int> sa = build_suffix_array();
  const vector<int> lcp = build_lcp();

  /// LCS of two strings A and B. The string s must be initialized in the
  /// constructor as the string (A + '$' + B).
  /// The string A starts at index 1 and ends at index (separator - 1).
  /// The string B starts at index (separator + 1) and ends at the end of the
  /// string.
  ///
  /// Time Complexity: O(n)
  int lcs(const int separator) {
    assert(!isalpha(this->s[separator]) && !isdigit(this->s[separator]));
    return _lcs(separator);
  }

  #ifdef BUILD_TABLE
  /// Compares two substrings beginning at indexes i and j of a fixed length.
  ///
  /// Time Complexity: O(1)
  int compare(const int i, const int j, const int length) {
    assert(0 <= i && i < this->n && 0 <= j && j < this->n);
    assert(i + length - 1 < this->n && j + length - 1 < this->n);
    return _compare(i, j, length);
  }
  #endif
};
// clang-format on
