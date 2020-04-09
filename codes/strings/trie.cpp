class Trie {
private:
  static const int INT_LEN = 31;
  // static const int INT_LEN = 63;

public:
  struct Node {
    map<char, Node *> next;
    int id;
    // cnt counts the number of words which pass in that node
    int cnt = 0;
    // word counts the number of words ending at that node
    int word_cnt = 0;

    Node(const int x) : id(x) {}
  };

private:
  int trie_size = 0;
  // contains the next id to be used in a node
  int node_cnt = 0;
  Node *trie_root = this->make_node();

private:
  Node *make_node() { return new Node(node_cnt++); }

  int trie_insert(const string &s) {
    Node *aux = this->root();
    for (const char c : s) {
      if (!aux->next.count(c))
        aux->next[c] = this->make_node();
      aux = aux->next[c];
      ++aux->cnt;
    }
    ++aux->word_cnt;
    ++this->trie_size;
    return aux->id;
  }

  void trie_erase(const string &s) {
    Node *aux = this->root();
    for (const char c : s) {
      Node *last = aux;
      aux = aux->next[c];
      --aux->cnt;
      if (aux->cnt == 0) {
        last->next.erase(c);
        aux = nullptr;
        break;
      }
    }
    if (aux != nullptr)
      --aux->word_cnt;
    --this->trie_size;
  }

  int trie_count(const string &s) {
    Node *aux = this->root();
    for (const char c : s) {
      if (aux->next.count(c))
        aux = aux->next[c];
      else
        return 0;
    }
    return aux->word_cnt;
  }

  int trie_query_xor_max(const string &s) {
    Node *aux = this->root();
    int ans = 0;
    for (const char c : s) {
      const char inv = (c == '0' ? '1' : '0');
      if (aux->next.count(inv)) {
        ans = (ans << 1ll) | (inv - '0');
        aux = aux->next[inv];
      } else {
        ans = (ans << 1ll) | (c - '0');
        aux = aux->next[c];
      }
    }
    return ans;
  }

public:
  Trie() {}

  Node *root() { return this->trie_root; }

  int size() { return this->trie_size; }

  /// Returns the number of nodes present in the trie.
  int node_count() { return this->node_cnt; }

  /// Inserts s in the trie.
  ///
  /// Returns the id of the last character of the string in the trie.
  ///
  /// Time Complexity: O(s.size())
  int insert(const string &s) { return this->trie_insert(s); }

  /// Inserts the binary representation of x in the trie.
  ///
  /// Time Complexity: O(log x)
  int insert(const int x) {
    assert(x >= 0);
    // converting x to binary representation
    return this->trie_insert(bitset<INT_LEN>(x).to_string());
  }

  /// Removes the string s from the trie.
  ///
  /// Time Complexity: O(s.size())
  void erase(const string &s) { this->trie_erase(s); }

  /// Removes the binary representation of x from the trie.
  ///
  /// Time Complexity: O(log x)
  void erase(const int x) {
    assert(x >= 0);
    // converting x to binary representation
    this->trie_erase(bitset<INT_LEN>(x).to_string());
  }

  /// Returns the number of maximum xor sum with x present in the trie.
  ///
  /// Time Complexity: O(log x)
  int query_xor_max(const int x) {
    assert(x >= 0);
    // converting x to binary representation
    return this->trie_query_xor_max(bitset<INT_LEN>(x).to_string());
  }

  /// Returns the number of strings equal to s present in the trie.
  ///
  /// Time Complexity: O(s.size())
  int count(const string &s) { return this->trie_count(s); }
};