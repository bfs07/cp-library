class Trie {
private:
  static const int INT_LEN = 31;
  // static const int INT_LEN = 63;

  struct Node {
    map<char, Node *> trans;
    bool word = false;
    // cont counts number of words which pass in that node
    int cont = 0;
  };
  Node *trie_head;
  int trie_size = 0;

private:
  Node *make_node() { return (new Node()); }

  void trie_insert(const string &s) {
    Node *aux = this->head();
    for (char c : s) {
      if (!(aux->trans).count(c))
        aux->trans[c] = make_node();
      aux = aux->trans[c];
      ++(aux->cont);
    }
    aux->word = true;
    ++this->trie_size;
  }

  void trie_erase(const string &s) {
    Node *aux = this->head();
    for (char c : s) {
      Node *last = aux;
      aux = aux->trans[c];
      if (--(aux->cont) == 0) {
        last->trans.erase(c);
        break;
      }
    }
    --this->trie_size;
  }

  int trie_query(const string &s) {
    Node *aux = this->head();
    for (char c : s) {
      if ((aux->trans).count(c))
        aux = aux->trans[c];
      else
        return 0;
    }
    return (*aux).cont;
  }

  int trie_query_xor_max(const string &s) {
    Node *aux = this->head();
    int ans = 0;
    for (char c : s) {
      char inv = (c == '0' ? '1' : '0');
      if ((aux->trans).count(inv)) {
        ans = ((ans << 1ll) | (inv - '0'));
        aux = aux->trans[inv];
      } else if ((aux->trans).count(c)) {
        ans = ((ans << 1ll) | (c - '0'));
        aux = aux->trans[c];
      }
    }
    return ans;
  }

public:
  /// Constructor that only creates a head node.
  ///
  /// Time Complexity: O(1)
  Trie() { this->trie_head = this->make_node(); }

  Node *head() { return this->trie_head; }

  int size() { return this->trie_size; }

  /// Inserts s in the trie.
  ///
  /// Time Complexity: O(log n)
  void insert(const string &s) { this->trie_insert(s); }

  /// Inserts the binary representation of x in the trie.
  ///
  /// Time Complexity: O(log n)
  void insert(const int x) {
    assert(x >= 0);
    // converting x to binary representation
    const string binary_rep = bitset<INT_LEN>(x).to_string();
    this->trie_insert(binary_rep);
  }

  /// Removes the string s from the trie.
  ///
  /// Time Complexity: O(log n)
  void erase(const string &s) { this->trie_erase(s); }

  /// Removes the binary representation of x from the trie.
  ///
  /// Time Complexity: O(log n)
  void erase(const int x) {
    assert(x >= 0);
    // converting x to binary representation
    const string binary_rep = bitset<INT_LEN>(x).to_string();
    this->trie_erase(binary_rep);
  }

  /// Returns the number of maximum xor sum with x present in the trie.
  ///
  /// Time Complexity: O(log n)
  int query_xor_max(const int x) {
    assert(x >= 0);
    // converting x to binary representation
    const string binary_rep = bitset<INT_LEN>(x).to_string();
    return this->trie_query_xor_max(binary_rep);
  }

  /// Returns the number of strings equal to s present in the trie.
  ///
  /// Time Complexity: O(log n)
  int query(const string &s) { return this->trie_query(s); }
};
