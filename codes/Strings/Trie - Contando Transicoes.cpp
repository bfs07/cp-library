// Contém também deleção de números e conversão

struct Node {
	map<char, Node*> trans;
	bool word = false;
  // cont counts number of words pass in that node
  int cont = 0;
};	

Node *head;

Node *makeNode() {
	return (new Node());
}

void insert(string &x) {
  Node *aux = head;
  for(char c: x) {
    if(!((aux->trans).count(c))) {
      aux->trans[c] = makeNode();
    }
    aux = aux->trans[c];
    (aux->cont)++;
  }
  aux->word = true;
}

void del(string &x) {
  Node *aux = head;
  for(char c: x) {    
    aux = aux->trans[c];
    (aux->cont)--;
  }
}


int query(string x) {
  Node *aux = head;
  for(char c: x) {
    if(((aux->trans).count(c))) {
      aux = aux->trans[c];
    } else {
      return 0;
    }
  }
  return (*aux).cont;
}


void init() {
	// Dont forget to initialize head
	head = makeNode();
}
