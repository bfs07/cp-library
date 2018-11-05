// OBS: ATÉ ∛N    DIVISORES DE N
vector<int> divisors(int n) {
	int sq = sqrt(n);
	vector<int> ans;
  for (int i=1; i<=sq+1; i++) {
    if (n%i==0) {
     	// If divisors are equal, print only one
     	if (n/i == i)
     	  ans.pb(i);
 	
     	else // Otherwise print both
        ans.pb(i), ans.pb(n/i);
    }
  }
  return ans;
}
