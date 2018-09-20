// mínimo num vetor arr de arr[0] ... arr[k-1], arr[1] ... arr[k], arr[2] ... arr[k+1]

void swma(vector<int> arr, int k) {
  deque<ii> window;
  for(int i = 0; i < arr.size(); i++) {
	  while(!window.empty() && window.back().ff > arr[i])
	    window.pop_back();
	  window.pb(ii(arr[i],i));
	  while(window.front().ss <= i - k)
	    window.pop_front();

  if(i >= k)
	  cout << ' ';
  if(i - k + 1 >= 0)
	  cout << window.front().ff;
	}
}
