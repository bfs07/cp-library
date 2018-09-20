int dp[2001][2001]; 
int moc(int q,int p,vector<ii> vec) {
	for(int i = 1; i <= q; i++)
	{
		for(int j = 1; j <= p;j++) {
			if(j >= vec[i-1].ff)
				dp[i][j] = max(dp[i-1][j],vec[i-1].ss + dp[i-1][j-vec[i-1].ff]);
			else 
				dp[i][j] = dp[i-1][j];
		}
	}
	return dp[q][p];
}
int main(int argc, char *argv[])
{
	int p,q;
	vector<ii> vec;
	cin >> p >> q;
	int x,y;
	for(int i = 0; i < q; i++) {
		   cin >> x >> y;
		   vec.push_back(make_pair(x,y));	
	}
	for(int i = 0; i <= p; i++)
		dp[0][i] = 0;
	for(int i = 1; i <= q; i++)
		dp[i][0] = 0;
	sort(vec.begin(),vec.end());
	cout << moc(q,p,vec) << endl;
}
