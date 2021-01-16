class Min_Queue {
private:
  /// Contains a pair (value, index), strictly decreasing.
  deque<pair<int, int>> d;

public:
  Min_Queue() {}

  int size() { return d.size(); }

  /// Removes all elements with index <= idx
  void pop(const int idx) {
    while (!d.empty() && d.front().second <= idx)
      d.pop_front();
  }

  /// Adds an element with value (val) and index (idx).
  void push(const int val, const int idx) {
    while (!d.empty() && d.back().first >= val)
      d.pop_back();
    d.emplace_back(val, idx);
  }

  int min_element() { return d.front().first; }
};