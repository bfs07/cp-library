int readInt(){
	int a = 0;
	char c;
	while( !(c >= '0' && c <= '9') ) c = getchar() ;
	while( c>= '0' && c <= '9') a = 10*a + (c - '0') , c = getchar() ;
	return a;
}
