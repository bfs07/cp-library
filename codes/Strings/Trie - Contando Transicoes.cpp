// Contém também deleção de números e conversão

struct Node {
	map<char, Node*> trans;
	bool word = false;
	int cont = 0;
};	

Node *head;

Node *makeNode() {
	return (new Node());
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

void insert(string &x) {
	Node *aux = head;
	int dep = 1;
	for(char c: x) {
		if(!((aux->trans).count(c))) {
			aux->trans[c] = makeNode();
		}
		aux = aux->trans[c];
		aux->cont++;
		dep++;
	}
	aux->word = true;
}

void del(string &x) {
	Node *aux = head;
	for(char c: x) {
		if((--(aux->trans[c].cont)) == 0) {
			aux->trans[c] = NULL;
			return;
		}
		aux = aux->trans[c];
	}
}

// example of query in problem to find maximum xor
string query(string x) {
	Node *aux = head;
	string r = "";
	for(char c: x) {
		if(aux->trans[c]) {
			r += c;
			aux = aux->trans[c];
		} else {
			r += comp(c);
			aux = aux->trans[comp(c)];
		}
	}
	return r;
}

void init() {
	// Dont forget to initialize head
	head = makeNode();
}
