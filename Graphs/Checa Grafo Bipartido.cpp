bool isBipartite(int src){
	
	int colorArr[V];
	for (int i = 0; i < V; ++i)
		colorArr[i] = -1;
	colorArr[src] = 1;

	queue <int> q; q.push(src);

	while (!q.empty()) {
		int u = q.front(); q.pop();

		// Find all non-colored adjacent vertices
		for (auto it = adj[u].begin(); it != adj[u].end(); it++) {
    //Return false if there is a self-loop 
		    if (u == *it)
		        return false;
			// An edge from u to v exists and destination v is not colored

			if (colorArr[*it] == -1) {
				// Assign alternate color to this adjacent v of u
	    	colorArr[*it] = 1 - colorArr[u];
				q.push(*it);
			}
			// An edge from u to v exists and destination v is colored with same color as u
			else if (colorArr[*it] == colorArr[u])
				return false;
		}
	}
	// If we reach here, then all adjacent vertices can be colored with 
	// alternate color
	return true;
}
