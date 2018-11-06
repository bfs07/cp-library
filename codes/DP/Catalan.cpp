// The first few Catalan numbers for n = 0, 1, 2, 3, ... 
// are 1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, ...
// Formula Recursiva: 
// cat(0) = 0
// cat(n+1) = somatorio(i from 0 to n)(cat(i)*cat(n-i))
// 
// Using Binomial Coefficient
// We can also use the below formula to find nth catalan number in O(n) time.
// Formula acima

// Returns value of Binomial Coefficient C(n, k)

int binomialCoeff(int n, int k) {
  int res = 1;
 
  // Since C(n, k) = C(n, n-k)
  if (k > n - k)
    k = n - k;
 
  // Calculate value of [n*(n-1)*---*(n-k+1)] / [k*(k-1)*---*1]
  for (int i = 0; i < k; ++i) {
      res *= (n - i);
      res /= (i + 1);
  }
 
    return res;
} 
// A Binomial coefficient based function to find nth catalan
// number in O(n) time
int catalan(int n) {
    // Calculate value of 2nCn
    int c = binomialCoeff(2*n, n);
 
    // return 2nCn/(n+1)
    return c/(n+1);
}
