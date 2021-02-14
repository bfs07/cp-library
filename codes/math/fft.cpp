/// Code copied from:
/// https://github.com/kth-competitive-programming/kactl/blob/08eb36f4bd9b8ce358e2f3fa8ffc329f62ebe811/content/numerical/FastFourierTransform.h

#define double long double
typedef complex<double> C;
typedef vector<double> vd;
void fft(vector<C> &a) {
  int n = a.size(), L = 31 - __builtin_clz(n);
  static vector<complex<double>> R(2, 1);
  // uncomment if you'll use only 'double'.
  // static vector<complex<long double>> R(2, 1);
  static vector<C> rt(2, 1); // (^ 10% faster if double)
  for (static int k = 2; k < n; k *= 2) {
    R.resize(n);
    rt.resize(n);
    auto x = polar(1.0L, acos(-1.0L) / k);
    for (int i = k; i < 2 * k; ++i)
      rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
  }
  vi rev(n);
  for (int i = 0; i < n; ++i)
    rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
  for (int i = 0; i < n; ++i)
    if (i < rev[i])
      swap(a[i], a[rev[i]]);
  for (int k = 1; k < n; k *= 2)
    for (int i = 0; i < n; i += 2 * k)
      for (int j = 0; j < k; ++j) {
        auto x = (double *)&rt[j + k],
             y = (double *)&a[i + j + k]; /// exclude-line
        C z(x[0] * y[0] - x[1] * y[1],
            x[0] * y[1] + x[1] * y[0]); /// exclude-line
        a[i + j + k] = a[i + j] - z;
        a[i + j] += z;
      }
}

/// Polynomial convolution of 'a' and 'b'.
///
/// Time Complexity: O(n log n)
vector<long long> convolve(const vd &a, const vd &b) {
  if (a.empty() || b.empty())
    return {};
  vd res(a.size() + b.size() - 1);
  int L = 32 - __builtin_clz(res.size()), n = 1 << L;
  vector<C> in(n), out(n);
  copy(all(a), begin(in));
  for (int i = 0; i < b.size(); ++i)
    in[i].imag(b[i]);
  fft(in);
  for (C &x : in)
    x *= x;
  for (int i = 0; i < n; ++i)
    out[i] = in[-i & (n - 1)] - conj(in[i]);
  fft(out);
  for (int i = 0; i < res.size(); ++i)
    res[i] = imag(out[i]) / (4 * n);
  vector<long long> arr(res.size());
  for (int i = 0; i < res.size(); ++i)
    arr[i] = round(res[i]);
  return arr;
}