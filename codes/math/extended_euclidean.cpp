int gcd, x, y;

// Ax + By = gcd(A,B)

void extended_euclidian(const int a, const int b) {
  if (b == 0) {
    gcd = a;
    x = 1;
    y = 0;
  } else {
    extended_euclidian(b, a % b);
    const int temp = x;
    x = y;
    y = temp - (a / b) * y;
  }
}
