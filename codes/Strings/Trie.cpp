struct No {
	map<char,No*> trans;
	bool word = false;
};

No* head;

No* makeNo() {
	return new No();
}

void insert(string x) {

	No* aux = head;

	for(char c: x) {
		if(aux->trans[c]) {
			aux = aux->trans[c];
		} else {
			aux = aux->trans[c] = makeNo();
		}
	}
	aux->word = true;
}

bool search(string s){
	no* aux = head;
	for(char c : s){
		if(aux->trans[c])
			aux = aux->trans[c];
		else
			return false;
	}
	return aux->word;
}

int main(){
	head = makeNo();
}
