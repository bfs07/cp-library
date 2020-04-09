class Aho {
private:
  // node of the output list
  struct Out_Node {
    vector<int> str_idx;
    Out_Node *next = nullptr;
  };

  vector<Trie::Node *> fail;
  Trie trie;
  // list of nodes of output
  vector<Out_Node *> out_node;
  const vector<string> arr;

  /// Time Complexity: O(number of characters in arr)
  void build_trie() {
    const int n = arr.size();
    int node_cnt = 1;

    for (int i = 0; i < n; ++i)
      node_cnt += arr[i].size();

    out_node.reserve(node_cnt);
    for (int i = 0; i < node_cnt; ++i)
      out_node.push_back(new Out_Node());

    fail.resize(node_cnt);
    for (int i = 0; i < n; ++i) {
      const int id = trie.insert(arr[i]);
      out_node[id]->str_idx.push_back(i);
    }

    this->build_failures();
  }

  /// Returns the fail node of cur.
  Trie::Node *find_fail_node(Trie::Node *cur, char c) {
    while (cur != this->trie.root() && !cur->next.count(c))
      cur = fail[cur->id];
    // if cur is pointing to the root node and c is not a child
    if (!cur->next.count(c))
      return trie.root();
    return cur->next[c];
  }

  /// Time Complexity: O(number of characters in arr)
  void build_failures() {
    queue<const Trie::Node *> q;

    fail[trie.root()->id] = trie.root();
    for (const pair<char, Trie::Node *> v : trie.root()->next) {
      q.emplace(v.second);
      fail[v.second->id] = trie.root();
      out_node[v.second->id]->next = out_node[trie.root()->id];
    }

    while (!q.empty()) {
      const Trie::Node *u = q.front();
      q.pop();

      for (const pair<char, Trie::Node *> x : u->next) {
        const char c = x.first;
        const Trie::Node *v = x.second;
        Trie::Node *fail_node = find_fail_node(fail[u->id], c);
        fail[v->id] = fail_node;

        if (!out_node[fail_node->id]->str_idx.empty())
          out_node[v->id]->next = out_node[fail_node->id];
        else
          out_node[v->id]->next = out_node[fail_node->id]->next;

        q.emplace(v);
      }
    }
  }

  vector<vector<pair<int, int>>> aho_find_occurrences(const string &text) {
    vector<vector<pair<int, int>>> ans(arr.size());
    Trie::Node *cur = trie.root();

    for (int i = 0; i < text.size(); ++i) {
      cur = find_fail_node(cur, text[i]);
      for (Out_Node *node = out_node[cur->id]; node != nullptr;
           node = node->next)
        for (const int idx : node->str_idx)
          ans[idx].emplace_back(i - (int)arr[idx].size() + 1, i);
    }
    return ans;
  }

public:
  /// Constructor that builds the trie and the failures.
  ///
  /// Time Complexity: O(number of characters in arr)
  Aho(const vector<string> &arr) : arr(arr) { this->build_trie(); }

  /// Searches in text for all occurrences of all strings in array arr.
  ///
  /// Time Complexity: O(text.size() + number of characters in arr)
  vector<vector<pair<int, int>>> find_occurrences(const string &text) {
    return this->aho_find_occurrences(text);
  }
};