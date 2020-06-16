/// Infix Expression | Prefix Expression | Postfix Expression
///      A + B       |     + A B         |       A B +
///    A + B * C     |    + A * B C      |     A B C * +
/// Time Complexity: O(n)
int infix_to_postfix(const string &infix) {
  map<char, int> prec;
  stack<char> op;
  string postfix;

  prec['+'] = prec['-'] = 1;
  prec['*'] = prec['/'] = 2;
  prec['^'] = 3;
  for (int i = 0; i < infix.size(); ++i) {
    char c = infix[i];
    if (is_digit(c)) {
      while (i < infix.size() && isdigit(infix[i])) {
        postfix += infix[i];
        ++i;
      }
      --i;
    } else if (isalpha(c))
      postfix += c;
    else if (c == '(')
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
