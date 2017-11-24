#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Node {
  Node() {}
  Node(int key, int left, int right)
      : m_key(key), m_left(left), m_right(right) {}

  int key() const { return m_key; }
  int left() const { return m_left; }
  int right() const { return m_right; }

private:
  int m_key = 0;
  int m_left = -1;
  int m_right = -1;
};

void inOrder(int root, const vector<Node> &tree, vector<int> &result) {
  if (root == -1) {
    return;
  }

  if (tree[root].left() != -1 && tree[tree[root].left()].key() >= tree[root].key()) {
    throw exception(); // trick for fast escaping from the recursion
  }

  inOrder(tree[root].left(), tree, result);
  result.push_back(tree[root].key());
  inOrder(tree[root].right(), tree, result);
}

vector<int> inOrder(const vector<Node> &tree) {
  vector<int> result;

  inOrder(0, tree, result);
  return result;
}



bool IsBinarySearchTree(const vector<Node> &tree, int index = 0) {
  if (tree.size() == 0) {
    return true;
  }

  try {
  auto in_order = inOrder(tree);
  int prev = in_order[0];
  for(int i = 1; i < in_order.size(); i++) {
    if (prev > in_order[i]) {
      return false;
    }
    prev = in_order[i];
  }
} catch(exception) {
  return false;
}
  return true;
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
