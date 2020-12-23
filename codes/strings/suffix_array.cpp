// #define LCP
// clang-format off
class Suffix_Array {
private:
  const string s;
  const int n;

private:
  /// OBS: Suffix Array build code imported from:
  /// https://github.com/gabrielpessoa1/Biblioteca-Maratona/blob/master/code/String/SuffixArray.cpp
  ///
  /// Time Complexity: O(n*(log n))
  vector<int> build_suffix_array() {
    int c = 0;
    vector<int> temp(n), posBucket(n), bucket(n), bpos(n), out(n);
    for (int i = 0; i < n; i++)
      out[i] = i;
    sort(out.begin(), out.end(),
         [&](int a, int b) { return this->s[a] < this->s[b]; });
    for (int i = 0; i < n; i++) {
      bucket[i] = c;
      if (i + 1 == n || this->s[out[i]] != this->s[out[i + 1]])
        c++;
    }
    for (int h = 1; h < n && c < n; h <<= 1) {
      for (int i = 0; i < n; i++)
        posBucket[out[i]] = bucket[i];
      for (int i = n - 1; i >= 0; i--)
        bpos[bucket[i]] = i;
      for (int i = 0; i < n; i++)
        if (out[i] >= n - h)
          temp[bpos[bucket[i]]++] = out[i];
      for (int i = 0; i < n; i++)
        if (out[i] >= h)
          temp[bpos[posBucket[out[i] - h]]++] = out[i] - h;
      c = 0;
      for (int i = 0; i + 1 < n; i++) {
        const int tmp = (bucket[i] != bucket[i + 1]) || (temp[i] >= n - h) ||
                        (posBucket[temp[i + 1] + h] != posBucket[temp[i] + h]);
        bucket[i] = c;
        c += tmp;
      }
      bucket[n - 1] = c++;
      temp.swap(out);
    }
    return out;
  }

  vector<int> build_inverse_suffix() {
    vector<int> inverse_suffix(this->n);
    for (int i = 0; i < this->n; ++i)
      inverse_suffix[sa[i]] = i;
    return inverse_suffix;
  }

  #ifdef LCP
  /// Builds the lcp (Longest Common Prefix) array for the string s.
  /// A value lcp[i] indicates length of the longest common prefix of the
  /// suffixes indexed by i and i + 1. Implementation of the Kasai's Algorithm.
  ///
  /// Time Complexity: O(n)
  vector<int> build_lcp() {
    vector<int> lcp(this->n, 0);
    for (int i = 0, k = 0; i < this->n; ++i) {
      if (inverse_suffix[i] == this->n - 1)
        k = 0;
      else {
        const int j = sa[inverse_suffix[i] + 1];
        while (i + k < this->n && j + k < this->n && s[i + k] == s[j + k])
          ++k;
        lcp[inverse_suffix[i]] = k;
        k -= k > 0;
      }
    }
    return lcp;
  }

  int _lcs(const int separator) {
    int ans = 0;
    for (int i = 0; i + 1 < this->sa.size(); ++i) {
      const int left = this->sa[i], right = this->sa[i + 1];
      if ((left < separator && right > separator) ||
          (left > separator && right < separator))
        ans = max(ans, lcp[i]);
    }
    return ans;
  }
  #endif

  /// Returns the minimum index, in the range [l, r], in which after advance i
  /// positions the character c is present.
  ///
  /// Time Complexity: O(log n)
  int lower(const char c, const int i, int l, int r) {
    int ans = -1;
    while (l <= r) {
      int mid = (l + r) / 2;
      if (sa[mid] + i < s.size() && s[sa[mid] + i] >= c) {
        ans = mid;
        r = mid - 1;
      } else
        l = mid + 1;
    }
    return ans;
  };

  /// Returns the maximum index in the range [l, r], such that after advance i
  /// positions the character c is present.
  ///
  /// Time Complexity: O(log n)
  int upper(const char c, const int i, int l, int r) {
    int ans = -1;
    while (l <= r) {
      int mid = (l + r) / 2;
      if (sa[mid] + i >= s.size() || s[sa[mid] + i] <= c) {
        ans = mid;
        l = mid + 1;
      } else
        r = mid - 1;
    }
    return ans;
  };


public:
  Suffix_Array(const string &s) : n(s.size()), s(s) {}

  const vector<int> sa = build_suffix_array();
  /// Position of the i-th character in suffix array.
  const vector<int> inverse_suffix = build_inverse_suffix();
  #ifdef LCP
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
  #endif

  void print() {
    for(int i = 0; i < n; ++i)
      cerr << s.substr(sa[i]) << endl;
  }

  /// Returns the range, inside the range [l, r], in which after advance i
  /// positions the character c is present.
  ///
  /// Time Complexity: O(log n)
  pair<int, int> range(const char c, const int i, int l, int r) {
    l = lower(c, i, l, r), r = upper(c, i, l, r);
    return min(l, r) == -1 ? pair<int, int>(-1, -1) : pair<int, int>(l, r);
  }
};
// clang-format on