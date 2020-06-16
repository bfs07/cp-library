int infix_to_postfix(const string &infix) {
  map<char, int> prec;
  stack<char> op;
  string postfix;

  prec['+'] = prec['-'] = 1;
  prec['*'] = prec['/'] = 2;
  prec['^'] = 3;
  for (int i = 0; i < infix.length(); ++i) {
    char c = infix[i];
    if (is_digit(c)) {
      while (i < infix.length() && is_digit(infix[i])) {
        postfix += infix[i];
        ++i;
      }
      --i;
    } else if (is_alpha(c)) {
      postfix += c;
    } else if (c == '(')
      op.push('(');
    else if (c == ')') {
      while (!op.empty() && op.top() != '(') {
        postfix += op.top();
        op.pop();
      }
      op.pop();
    } else {
      while (!op.empty() && prec[op.top()] >= prec[c]) {
        postfix += op.top();
        op.pop();
      }
      op.push(c);
    }
  }
  while (!op.empty()) {
    postfix += op.top();
    op.pop();
  }
  return postfix;
}
