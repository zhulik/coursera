#include <algorithm>
#include <iostream>
#include <sys/resource.h>
#include <vector>

using namespace std;

template<typename T> void print(const vector<T> &row) {
  for(auto item: row) {
    cout << item << " ";
  }
  cout << endl;
}

class Node {
public:
  Node() : m_parent(nullptr) {}

  void setParent(Node *parent) {
    m_parent = parent;
    m_parent->m_children.push_back(this);
  }
  Node *parent() const { return m_parent; }

  void setKey(int key) { m_key = key; }
  int key() const { return m_key; };

  int depth(int m = 0) const {
    if (m_children.empty())
      return m + 1;

    vector<int> depths(m_children.size());
    transform(m_children.begin(), m_children.end(), depths.begin(),
              [m](auto n) { return n->depth(m + 1); });

    return *max_element(depths.begin(), depths.end());
  }

private:
  int m_key;
  Node *m_parent;
  vector<Node *> m_children;
};

int main_with_large_stack_space() {
  ios_base::sync_with_stdio(0);
  int n;
  cin >> n;

  vector<Node*> nodes;
  nodes.resize(n);
  for(int i = 0; i < n; i++) {
    nodes[i] = new Node();
  }
  Node *root;
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    cin >> parent_index;
    if (parent_index >= 0)
      nodes[child_index]->setParent(nodes[parent_index]);
    nodes[child_index]->setKey(child_index);
    if (parent_index == -1) {
      root = nodes[child_index];
    }
  }

  cout << root->depth() << endl;
  return 0;
}

int main(int argc, char **argv) {
  const rlim_t kStackSize = 16 * 1024 * 1024; // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0) {
    if (rl.rlim_cur < kStackSize) {
      rl.rlim_cur = kStackSize;
      result = setrlimit(RLIMIT_STACK, &rl);
      if (result != 0) {
        cerr << "setrlimit returned result = " << result << endl;
      }
    }
  }
  return main_with_large_stack_space();
}
