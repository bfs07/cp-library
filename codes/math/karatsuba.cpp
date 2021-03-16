/// Code copied from:
/// https://github.com/iam0rch1d/algospot/blob/98476cf0513967cd2481d8dc8dc0201598420979/fanmeeting.cpp

const int MINIMUM_KARATSUBA_A_SIZE = 50;

vector<int> multiply(const vector<int> &a, const vector<int> &b) {
  vector<int> multiplication(a.size() + b.size() + 1, 0);
  for (int i = 0; i < a.size(); i++)
    for (int j = 0; j < b.size(); j++)
      multiplication[i + j] += a[i] * b[j];
  return multiplication;
}

void add(vector<int> &to, vector<int> &howMuch, int howMuchExponent) {
  const int howMuchSize = howMuch.size();

  if (to.size() < howMuch.size() + howMuchExponent)
    to.resize(howMuch.size() + howMuchExponent);

  for (int i = 0; i < howMuchSize; i++)
    to[howMuchExponent + i] += howMuch[i];
}

void subtract(vector<int> &from, vector<int> &howMuch) {
  for (int i = 0; i < howMuch.size(); i++)
    from[i] -= howMuch[i];
}

/// Multiplies two polynomials a and b using Karatsuba algorithm.
///
/// Time complexity: O(n^(1.59))
vector<int> multiplyKaratsuba(const vector<int> &a, const vector<int> &b) {
  const int aSize = a.size(), bSize = b.size();

  if (aSize < bSize)
    return multiplyKaratsuba(b, a);

  if (aSize == 0 || bSize == 0)
    return vector<int>();

  if (aSize < MINIMUM_KARATSUBA_A_SIZE)
    return multiply(a, b);

  const int aNumberHalfSize = aSize / 2;
  vector<int> aDivision0(a.begin(), a.begin() + aNumberHalfSize);
  vector<int> aDivision1(a.begin() + aNumberHalfSize, a.end());
  vector<int> bDivision0(b.begin(),
                         b.begin() + min<int>(bSize, aNumberHalfSize));
  vector<int> bDivision1(b.begin() + min<int>(bSize, aNumberHalfSize), b.end());
  vector<int> karatsubaFactor0 = multiplyKaratsuba(aDivision0, bDivision0);
  vector<int> karatsubaFactor2 = multiplyKaratsuba(aDivision1, bDivision1);

  add(aDivision0, aDivision1, 0);
  add(bDivision0, bDivision1, 0);

  vector<int> karatsubaFactor1 = multiplyKaratsuba(aDivision0, bDivision0);
  subtract(karatsubaFactor1, karatsubaFactor0);
  subtract(karatsubaFactor1, karatsubaFactor2);

  vector<int> multiplication;
  add(multiplication, karatsubaFactor0, 0);
  add(multiplication, karatsubaFactor1, aNumberHalfSize);
  add(multiplication, karatsubaFactor2, aNumberHalfSize + aNumberHalfSize);

  return multiplication;
}