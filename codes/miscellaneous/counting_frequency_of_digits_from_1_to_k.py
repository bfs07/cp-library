def check(k):
  ans = [0] * 10
  for d in range(1, 10):
    pot = 10
    last = 1
    for i in range(20):
      v = (k // pot * last) + min(max(0, ((k % pot) - (last * d)) + 1), last)
      ans[d] += v
      pot *= 10
      last *= 10

  return ans
