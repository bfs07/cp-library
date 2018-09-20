struct cmp {
	bool operator(ii a, ii b) {
	//ordena primeiro pelo first(decrescente), dps pelo second(crescente)
		if(a.first == b.first)
			return a.second < b.second;
		return a.first > b.first; 
	}
}
Ex: pq<ii,vector<ii>,cmp> fila;
