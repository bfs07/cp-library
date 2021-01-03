/// Splits a string into a vector. A separator can be specified
/// EX: str=A-B-C -> split -> x = {A,B,C}
vector<string> split(const string &s, char separator = ' ') {
  stringstream ss(s);
  string item;
  vector<string> tokens;
  while (getline(ss, item, separator))
    tokens.emplace_back(item);
  return tokens;
}
int main() {
  vector<string> x = split("cap-one-best-opinion-language", '-');
  // x = {cap,one,best,opinion,language};
}