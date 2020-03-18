int gcd(int a, int b) { 
  if (a == 0) 
    return b; 
  return gcd(b%a, a); 
} 

int power(int x, int p, int MOD) {
  if(p == 0)
    return 1%MOD;
  if(p == 1) 
    return x%MOD;
  int res = power(x, p/2, MOD);
  res = (long long)res*res%MOD;
  if(p&1) 
    res = (long long)res*x%MOD;
  return res;
}

// A*B = x (mod m)
// B = x * A^(-1)
// Function to find modular inverse of a under modulo m 
// Assumption: m is prime 
int modInverse(int a, int mod) { 
  int g = gcd(a, mod); 
  if (g != 1) 
      return -1; 
  else
    // If a and m are relatively prime, then modulo inverse 
    // is a^(m-2) mod m 
    return power(a, mod-2, mod);
} 