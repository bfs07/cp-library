int main() {
map<char,int> prec;
stack<char> op;

string postfix;
string infix;
cin >> infix;

prec['+'] = prec['-'] = 1;
prec['*'] = prec['/'] = 2;
prec['^'] = 3;
for(int i = 0; i < infix.length(); i++) {
  char x = infix[i];
  if('0' <= x && x <= '9') {
    for(i;i < infix.length() && ('0' <= infix[i] && infix[i] <= '9');i++)
      postfix += infix[i];
    i--;
  } else if(('a' <= x && x <= 'z') || ('A' <= x && x <= 'Z')) {
    postfix += x;
  } else if (x == '(')
    op.push('(');
  else if(x == ')') {
    while(!op.empty() && op.top() != '(') {
      postfix += op.top();
      op.pop();
    }
    op.pop();
  } else {
    while(!op.empty() && prec[op.top()] >= prec[x]) {
    postfix += op.top();
    op.pop();
  }
  op.push(x);
  }
}
while(!op.empty()) {
postfix += op.top();
op.pop();
}
cout << postfix << endl;
}  
