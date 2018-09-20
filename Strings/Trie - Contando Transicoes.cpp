// Contém também deleção de números e conversão
// NUMERO TA EM LONG LONG
struct No {
	map<char,pair<No*,int> > trans;
	bool word = false;
};	

No *head;

No *makeNo() {
	return new No();
}

char comp(char x) {
	return (x == '0' ? '1':'0');
}

string toBin(int x) {
	string r;
	for(int i = 32; i >= 0; i--)
		r += ((bool)(x & (1ll<<i)) + '0');
	return r;
}

string toBinQuery(int x) {
	string r = "";
	for(int i = 32; i >= 0; i--) {
		if((bool)(x & (1ll<<i)))
			r += '0';
		 else
			r += '1';
		
	}
	return r;
}

int toInt(string x) {
	int c = 0;
	for(int i = 0; i < 33; i++) {
		if(x[i] == '1')
			c += (1ll<<(32-i));
	}
	return c;
}

void insert(string x) {
	No *aux = head;
	for(char c: x) {

		if(aux->trans[c].ff) {
			aux->trans[c].ss += 1;
		} else {
			aux->trans[c].ff = makeNo();
			aux->trans[c].ss = 1;
		}
		aux = aux->trans[c].ff;
	}
	aux->word = true;
}

void del(string x) {
	No *aux = head;
	for(char c: x) {
		if((--(aux->trans[c].ss)) == 0) {
			aux->trans[c].ff = NULL;
			return;
		}
		aux = aux->trans[c].ff;
	}
}

string query(string x) {
	No *aux = head;
	string r = "";
	for(char c: x) {
		if(aux->trans[c].ff) {
			r += c;
			aux = aux->trans[c].ff;
		} else {
			r += comp(c);
			aux = aux->trans[comp(c)].ff;
		}
	}
	return r;
}

int main() {
	No *head = makeNo();
}
