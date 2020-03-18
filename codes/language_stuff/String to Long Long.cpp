string s = "0xFFFF"; int base = 16;
string::size_type sz = 0;
int ll = stoll(s,&sz,base); //  ll = 65535, sz = 6;
OBS: Não precisa colocar o sz, pode colocar 0; // stoll(s,0,base);