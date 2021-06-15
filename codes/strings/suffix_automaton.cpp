class Suffix_Automaton {
private:
  struct state {
    map<char, int> next;
    /// Length of the current substring which is the longest in the ith class.
    /// The range of substring lengths of this class is the following:
    /// [st[st[u].prev].len + 1, len].
    const int len;
    /// Contains a link to the previous substring from the ith class. Contains
    /// unique substrings from next(prev) this state.
    int prev;
    /// Contains the index of the last position of the first substring.
    const int first_pos;
    /// Whether the ith node is terminal or not.
    bool is_terminal = false;

    state(const map<char, int> next, const int len, const int prev,
          const int first_pos)
        : next(next), len(len), prev(prev), first_pos(first_pos) {}
  };
  vector<state> st;
  int last = 0;

  void build(const string &s) {
    st.emplace_back(map<char, int>(), 0, -1, -1);

    for (int i = 0; i < s.size(); ++i) {
      st.emplace_back(map<char, int>(), i + 1, 0, i);
      const int cur = (int)st.size() - 1;

      int prev = last;
      while (prev >= 0 && !st[prev].next.count(s[i])) {
        st[prev].next[s[i]] = cur;
        prev = st[prev].prev;
      }

      if (prev != -1) {
        const int q = st[prev].next[s[i]];
        if (st[prev].len + 1 == st[q].len) {
          st[cur].prev = q;
        } else {
          st.emplace_back(st[q].next, st[prev].len + 1, st[q].prev,
                          st[q].first_pos);
          const int qq = (int)st.size() - 1;
          st[q].prev = st[cur].prev = qq;
          while (prev >= 0) {
            auto it = st[prev].next.find(s[i]);
            if (it == st[prev].next.end() || it->second != q)
              break;
            it->second = qq;
            prev = st[prev].prev;
          }
        }
      }
      last = cur;
    }
  }

  void find_terminals() {
    int p = last;
    while (p > 0) {
      st[p].is_terminal = true;
      p = st[p].prev;
    }
  }

  vector<int> dp_ocur;
  int _ocur(const int idx) {
    int &ret = dp_ocur[idx];
    if (~ret)
      return ret;
    ret = st[idx].is_terminal;
    for (const pair<char, int> &p : st[idx].next)
      ret += _ocur(p.second);
    return ret;
  }

public:
  Suffix_Automaton(const string &s) {
    st.reserve(2 * s.size());
    build(s);
    find_terminals();
  }

  int size() { return st.size(); }

  int prev(const int idx) { return st[idx].prev; }

  int len(const int idx) { return st[idx].len; }

  int first_pos(const int idx) { return st[idx].first_pos; }

  /// Returns the next state from state cur with character c.
  /// Returns -1 if this state doesn't exists.
  int next(const int cur, const char c) {
    auto it = st[cur].next.find(c);
    return it == st[cur].next.end() ? -1 : it->second;
  }

  void print() {
    cerr << "Terminals" << endl;
    for (int i = 0; i < st.size(); ++i)
      if (st[i].is_terminal)
        cerr << i << ' ';
    cerr << endl;
    cerr << "Edges" << endl;
    for (int i = 0; i < st.size(); ++i)
      for (auto [a, b] : st[i].next)
        cerr << i << ' ' << b << ' ' << a << endl;
  }

  /// Returns the number of occurrences of the pattern ending at state idx.
  ///
  /// Time Complexity: O(n), amortized for q queries.
  int ocur(const int idx) {
    if (dp_ocur.empty())
      dp_ocur.resize(st.size(), -1);
    return _ocur(idx);
  }

  /// Returns the state in which the pattern s ends.
  ///
  /// Time complexity: O(s.size())
  int find(const string &s) {
    int cur = 0;
    for (char c : s) {
      auto it = st[cur].next.find(c);
      if (it == st[cur].next.end())
        return -1;
      cur = it->second;
    }
    return cur;
  }
};

/// To output all occurrences build the inverse_prev adjacency list
///
/// for (int i = 1; i < st.size(); ++i)
///   inverse_prev[st[i].prev].emplace_back(i);
///
/// Then take all occurrences from state cur (where the substring ends)
///
/// void output_all_occurrences(int cur, int pat_length) {
///   occ.emplace_back(st[cur].first_pos - pat_length + 1);
///   for (const int u : inverse_prev[cur])
///     output_all_occurrences(u, pat_length);
/// }
///
/// Take care and remove all duplicates after that
///
/// sort(occ.begin(), occ.end())
/// occ.resize(unique(occ.begin(), occ.end()) - occ.begin())