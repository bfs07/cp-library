class Suffix_Automaton {
private:
  struct state {
    map<char, int> next;
    /// Length of the current substring which is the longest in the ith class.
    /// The range of substring lengths of this class is the following:
    /// [st[st[u].link].len + 1, len].
    const int len;
    /// Contains a link to the state containing the longest suffix of the
    /// current class which isn't present in it.
    int link;
    /// Contains the index of the last position of the first substring.
    const int first_pos;
    /// Whether the ith node is terminal or not.
    bool is_terminal = false;

    state(const map<char, int> next, const int len, const int link,
          const int first_pos)
        : next(next), len(len), link(link), first_pos(first_pos) {}
  };
  vector<state> st;
  int last = 0;

  /// Time Complexity: O(n*log(alphabet_size))
  void build(const string &s) {
    st.emplace_back(map<char, int>(), 0, -1, -1);

    for (int i = 0; i < s.size(); ++i) {
      st.emplace_back(map<char, int>(), i + 1, 0, i);
      const int cur = (int)st.size() - 1;

      int link = last;
      while (link >= 0 && !st[link].next.count(s[i])) {
        st[link].next[s[i]] = cur;
        link = st[link].link;
      }

      if (link != -1) {
        const int q = st[link].next[s[i]];
        if (st[link].len + 1 == st[q].len) {
          st[cur].link = q;
        } else {
          st.emplace_back(st[q].next, st[link].len + 1, st[q].link,
                          st[q].first_pos);
          const int qq = (int)st.size() - 1;
          st[q].link = st[cur].link = qq;
          while (link >= 0) {
            auto it = st[link].next.find(s[i]);
            if (it == st[link].next.end() || it->second != q)
              break;
            it->second = qq;
            link = st[link].link;
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
      p = st[p].link;
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

  int link(const int idx) { return st[idx].link; }

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

/// OUTPUT ALL OCCURRENCES
/// To output all occurrences build the inverse_link adjacency list
///
/// for (int i = 1; i < st.size(); ++i)
///   inverse_link[st[i].link].emplace_back(i);
///
/// Then take all occurrences from state cur (where the substring ends)
///
/// void output_all_occurrences(int cur, int pat_length) {
///   occ.emplace_back(st[cur].first_pos - pat_length + 1);
///   for (const int u : inverse_link[cur])
///     output_all_occurrences(u, pat_length);
/// }
///
/// Take care and remove all duplicates after that
///
/// sort(occ.begin(), occ.end())
/// occ.resize(unique(occ.begin(), occ.end()) - occ.begin())

/// LAST POSITION
/// Since the link of the current state represents the longest suffix of the
/// current class which is not present in it, we can calculate the last
/// position of the current class using dp.
//
// vector<int> dp_last_pos;
// vector<vector<int>> inverse_link;
// void pre_compute() {
//   dp_last_pos.resize(st.size(), -1);
//   inverse_link.resize(st.size());
//   for (int i = 1; i < st.size(); ++i)
//     inverse_link[st[i].link].emplace_back(i);
// }
//
// int last_pos(const int u) {
//   int &ret = dp_last_pos[u];
//   if (~ret)
//     return ret;
//   ret = st[u].first_pos;
//   for (const int v : inverse_link[u])
//     ret = max(ret, last_pos(v));
//   return ret;
// }