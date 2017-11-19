#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>

using namespace std;
typedef unsigned long long ull;

static const size_t multiplier = 263;
static const ull prime = 18446744073709551557;

ull hash_func(const string &t, size_t from, size_t to) {
  ull hash = 0;
  for (int i = (int)to - 1; i >= (int)from; --i)
    hash = (hash * multiplier + t[i]) % prime;
  return hash;
}

vector<ull> precompute_hashes(const string &t, size_t p) {
  vector<ull> h(t.size() - p + 1);

  h[t.size() - p] = hash_func(t, t.size() - p, t.size());
  ull y = 1;
  for (int i = 0; i < p; i++) {
    y = (y * multiplier) % prime;
  }
  for (int i = (int)t.size() - (int)p - 1; i >= 0; --i) {
    h[i] = (multiplier * h[i + 1] + t[i] - y * t[i + p]) % prime;
  }

  return h;
}

vector<size_t> get_occurrences(const string &p, const string &t) {
  vector<size_t> ans;
  auto ph = hash_func(p, 0, p.size());
  auto hashes = precompute_hashes(t, p.size());
  for (size_t i = 0; i < hashes.size(); i++) {
    if (hashes[i] == ph && t.substr(i, p.size()) == p) {
      ans.push_back(i);
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  string pattern, text;
  cin >> pattern >> text;
  auto output = get_occurrences(pattern, text);
  for (auto o : output)
    cout << o << " ";
  cout << endl;
  return 0;
}
