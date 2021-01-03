string s = "0xFFFF";
int base = 16;
string::size_type sz = 0;
int ll = stoll(s, &sz, base);
// ll = 65535, sz = 6;
// if base is equal to 10 you may leave it empty.
// OBS: You can place anything (like 0) instead of sz stoll(s,0,base);