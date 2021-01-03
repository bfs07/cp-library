sort(arr.begin(), arr.end());
arr.resize(unique(arr.begin(), arr.end()) - arr.begin());