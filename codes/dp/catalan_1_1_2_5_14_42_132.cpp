// The first few Catalan numbers for n = 0, 1, 2, 3, ...
// are 1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, ...
// Recursive formula:
// cat(0) = 0
// cat(n+1) = sum(i from 0 to n)(cat(i)*cat(n-i))
//
// Using Binomial Coefficient
// We can also use the below formula to find nth catalan number in O(n) time.

// Returns value of Binomial Coefficient C(n, k)

// REQUIRES combinatorics.cpp
int catalan(int n) {
  return comb.fat(2 * n) * comb.inv(comb.fat(n + 1)) % MOD *
         comb.inv(comb.fat(n)) % MOD;
}