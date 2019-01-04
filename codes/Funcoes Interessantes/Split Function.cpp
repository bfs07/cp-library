// SEPARA STRING POR UM DELIMITADOR
// EX: str=A-B-C split -> x = {A,B,C} 
vector<string> split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}
int main () {
  vector<string> x = split("cap-one-best-opinion-language", '-'); 
// x = {cap,one,best,opinion,language};
}