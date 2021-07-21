// Problem: Sum from l to r
// See also MO'S ALGORITHM
// --------------------------------------
int getId(int indx, int blockSZ) { return indx / blockSZ; }

void init(int sz) {
  for (int i = 0; i <= sz; i++)
    BLOCK[i] = inf;
}

int query(int left, int right) {
  int startBlockIndex = left / sqrt;
  int endIBlockIndex = right / sqrt;
  int sum = 0;
  for (int i = startBlockIndex + 1; i < endIBlockIndex; i++) {
    sum += blockSums[i];
  }
  for (i = left...(startBlockIndex * BLOCK_SIZE - 1))
    sum += a[i];
  for (j = endIBlockIndex * BLOCK_SIZE... right)
    sum += a[i];
}