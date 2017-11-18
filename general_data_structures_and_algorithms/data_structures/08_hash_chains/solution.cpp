#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

size_t hash_func(const string &s) {
  static const size_t multiplier = 263;
  static const size_t prime = 1000000007;
  unsigned long long hash = 0;
  for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i)
    hash = (hash * multiplier + s[i]) % prime;
  return hash;
}

class Query {
public:
  string type() const { return m_type; };
  void setType(const string &t) { m_type = t; }

  string s() const { return m_s; };
  void setS(const string &s) { m_s = s; }

  size_t index() const { return m_index; }
  void setIndex(size_t i) { m_index = i; }

private:
  string m_type, m_s;
  size_t m_index;
};

template <typename K> class HashTable {
public:
  explicit HashTable(size_t bucket_count) : m_bucket_count(bucket_count) {
    m_buckets = vector<list<K>>(bucket_count);
  };

  void add(const K &key) {
    if (!find(key)) {
      bucket(key).push_front(key);
    }
  };

  void del(const K &key){
    auto &b = bucket(key);
    auto it = ::find(b.begin(), b.end(), key);
    if (it != b.end()) {
      b.erase(it);
    }
  };

  bool find(const K &key) {
    for (auto s :bucket(key)) {
      if (s == key) {
        return true;
      }
    }
    return false;
  };

  list<K> check(size_t i) { return m_buckets[i]; };

private:
  size_t m_bucket_count;
  vector<list<K>> m_buckets;

  list<K> &bucket(const K &key) {
    return m_buckets[hash_func(key) % m_bucket_count];
  }
};

string writeSearchResult(bool was_found) { return was_found ? "yes" : "no"; }

Query readQuery() {
  Query query;
  string type, s;
  size_t index;
  cin >> type;
  query.setType(type);
  if (query.type() != "check") {
    cin >> s;
    query.setS(s);
  } else {
    cin >> index;
    query.setIndex(index);
  }
  return query;
}

vector<Query> readQueries() {
  int n;
  cin >> n;
  vector<Query> result(n);
  for (int i = 0; i < n; ++i)
    result[i] = readQuery();

  return result;
}

int main() {
  ios_base::sync_with_stdio(false);
  int bucket_count;
  cin >> bucket_count;
  HashTable<string> table(bucket_count);
  auto queries = readQueries();
  for (auto q : queries) {
    if (q.type() == "add") {
      table.add(q.s());
    }
    if (q.type() == "del") {
      table.del(q.s());
    }
    if (q.type() == "find") {
      cout << writeSearchResult(table.find(q.s())) << endl;
    }
    if (q.type() == "check") {
      for (auto s : table.check(q.index())) {
        cout << s << " ";
      }
      cout << endl;
    }
  }
  return 0;
}
