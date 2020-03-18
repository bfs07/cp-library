// arr = {10,20,20,20,30,20,20,10}
it = unique(arr.begin(), arr.end());
// arr = {10,20,30,20,10, iterator aponta pra aqui, ...}
arr.resize(distance(arr.begin(), it));
// arr = {10,20,30,20,10}