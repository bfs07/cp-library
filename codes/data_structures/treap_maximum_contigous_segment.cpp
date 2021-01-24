bool full(Node *node) { return node->cntl == get_size(node); }

// Range Sum
void merge_nodes(Node *node) {
  node->ans = 1;
  node->l = node->val;
  node->cntl = 1;
  node->r = node->val;
  node->cntr = 1;

  if (node->left) {
    node->ans = max(node->ans, node->left->ans);
    node->cntl = node->left->cntl;
    node->l = node->left->l;
    if (node->left->r == node->val) {
      node->ans = max(node->ans, node->left->cntr + 1);
      if (full(node->left))
        node->cntl = node->left->cntr + 1;
      if (!node->right) {
        node->r = node->val;
        node->cntr = node->left->cntr + 1;
      }
    }
  }

  if (node->right) {
    node->ans = max(node->ans, node->right->ans);
    node->cntr = node->right->cntr;
    node->r = node->right->r;
    if (node->right->l == node->val) {
      node->ans = max(node->ans, node->right->cntl + 1);
      if (full(node->right))
        node->cntr = node->right->cntl + 1;
      if (!node->left) {
        node->l = node->val;
        node->cntl = node->right->cntl + 1;
      }
    }
  }

  if (node->left && node->right) {
    node->ans = max({node->ans, node->left->ans, node->right->ans});
    if (node->left->r == node->val && node->right->l == node->val) {
      node->ans = max(node->ans, node->left->cntr + 1 + node->right->cntl);
      if (full(node->left))
        node->cntl = node->left->cntl + 1 + node->right->cntl;
      if (full(node->right))
        node->cntr = node->left->cntr + 1 + node->right->cntr;
    }
  }

  node->ans = max({node->ans, node->cntl, node->cntr});
}