// Created by tysm.

/// Returns a tuple containing the gcd(a, b) and the roots for
/// a*x + b*y = gcd(a, b).
///
/// Time Complexity: O(log(min(a, b))).
tuple<uint, int, int> extended_gcd(uint a, uint b) {
  int x = 0, y = 1, x1 = 1, y1 = 0;
  while (a != 0) {
    uint q = b / a;
    tie(x, x1) = make_pair(x1, x - q * x1);
    tie(y, y1) = make_pair(y1, y - q * y1);
    tie(a, b) = make_pair(b % a, a);
  }
  return make_tuple(b, x, y);
}

/// Provides modular operations such as +, -, *, /, multiplicative inverse and
/// binary exponentiation.
///
/// Time Complexity: O(1).
template <uint M> struct modular {
  static_assert(0 < M && M <= INT_MAX, "M must be a positive 32 bits integer.");

  uint value;

  modular() : value(0) {}

  template <typename T> modular(const T value) {
    if (value >= 0)
      this->value = ((uint)value < M ? value : (uint)value % M);
    else {
      uint abs_value = (-(uint)value) % M;
      this->value = (abs_value == 0 ? 0 : M - abs_value);
    }
  }

  template <typename T> explicit operator T() const { return value; }

  modular operator-() const { return modular(value == 0 ? 0 : M - value); }

  modular &operator+=(const modular &rhs) {
    if (rhs.value >= M - value)
      value = rhs.value - (M - value);
    else
      value += rhs.value;
    return *this;
  }

  modular &operator-=(const modular &rhs) {
    if (rhs.value > value)
      value = M - (rhs.value - value);
    else
      value -= rhs.value;
    return *this;
  }

  modular &operator*=(const modular &rhs) {
    value = (uint64_t)value * rhs.value % M;
    return *this;
  }

  modular &operator/=(const modular &rhs) { return *this *= inverse(rhs); }

  /// Computes pow(b, e) % M.
  ///
  /// Time Complexity: O(log(e)).
  friend modular exp(modular b, uint e) {
    modular res = 1;
    for (; e > 0; e >>= 1) {
      if (e & 1)
        res *= b;
      b *= b;
    }
    return res;
  }

  /// Computes the modular multiplicative inverse of a with mod M.
  ///
  /// Time Complexity: O(log(a)).
  friend modular inverse(const modular &a) {
    assert(a.value > 0);
    auto aux = extended_gcd(a.value, M);
    assert(get<0>(aux) == 1); // a and M must be coprimes.
    return modular(get<1>(aux));
  }

  friend modular operator+(modular lhs, const modular &rhs) {
    return lhs += rhs;
  }

  friend modular operator-(modular lhs, const modular &rhs) {
    return lhs -= rhs;
  }

  friend modular operator*(modular lhs, const modular &rhs) {
    return lhs *= rhs;
  }

  friend modular operator/(modular lhs, const modular &rhs) {
    return lhs /= rhs;
  }

  friend bool operator==(const modular &lhs, const modular &rhs) {
    return lhs.value == rhs.value;
  }

  friend bool operator!=(const modular &lhs, const modular &rhs) {
    return !(lhs == rhs);
  }

  friend string to_string(const modular &a) { return to_string(a.value); }

  friend ostream &operator<<(ostream &lhs, const modular &rhs) {
    return lhs << to_string(rhs);
  }
};

using mint = modular<MOD>;
