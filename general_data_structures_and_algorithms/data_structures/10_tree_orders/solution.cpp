#include <algorithm>
#include <iostream>
#include <vector>

#include <sys/resource.h>

using namespace std;

template <typename T> class TreeOrders {
public:
  TreeOrders(vector<T> key, vector<T> left, vector<T> right)
      : m_key(key), m_left(left), m_right(right) {}

  vector<T> in_order() {
    vector<T> result;

    in_order(0, result);
    return result;
  }

  vector<T> pre_order() {
    vector<T> result;

    pre_order(0, result);
    return result;
  }

  vector<T> post_order(int root = 0) {
    vector<T> result;

    post_order(0, result);
    return result;
  }

private:
  vector<T> m_key;
  vector<T> m_left;
  vector<T> m_right;

  void in_order(int root, vector<T> &result) {
    if (root == -1) {
      return;
    }

    in_order(m_left[root], result);
    result.push_back(m_key[root]);
    in_order(m_right[root], result);
  }

  void pre_order(int root, vector<T> &result) {
    if (root == -1) {
      return;
    }

    result.push_back(m_key[root]);
    pre_order(m_left[root], result);
    pre_order(m_right[root], result);
  }

  void post_order(int root, vector<T> &result) {
    if (root == -1) {
      return;
    }

    post_order(m_left[root], result);
    post_order(m_right[root], result);
    result.push_back(m_key[root]);
  }
};

template <typename T> void print(vector<T> a) {
  for (size_t i = 0; i < a.size(); i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << a[i];
  }
  cout << endl;
}

int main_with_large_stack_space() {
  ios_base::sync_with_stdio(0);
  int n;
  cin >> n;
  vector<int> key(n), left(n), right(n);

  for (int i = 0; i < n; i++) {
    cin >> key[i] >> left[i] >> right[i];
  }
  TreeOrders<int> t(key, left, right);
  print(t.in_order());
  print(t.pre_order());
  print(t.post_order());
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
        std::cerr << "setrlimit returned result = " << result << std::endl;
      }
    }
  }

  return main_with_large_stack_space();
}
