#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T> class Query {
public:
  T number() const { return m_number; }
  void setNumber(T n) { m_number = n; }

  string type() const { return m_type; }
  void setType(const string &t) { m_type = t; }

  string name() const { return m_name; }
  void setName(const string &n) { m_name = n; }

private:
  string m_type;
  string m_name;
  T m_number;
};

class DirectIndexPhoneBook {
public:
  DirectIndexPhoneBook() {
    m_list = vector<string>(10000000, "not found");
  }

  void add(long long n, string name) {m_list[n] = name;};
  void del(long long n) {m_list[n] = "not found";};
  string find(long long n) const {return m_list[n];};


private:
  vector<string> m_list;
};

vector<Query<long long>>
read_queries() {
  long long n;
  cin >> n;
  vector<Query<long long>> queries(n);
  string type, name;
  long long number;
  for (int i = 0; i < n; ++i) {
    cin >> type;
    queries[i].setType(type);
    if (queries[i].type() == "add") {
      cin >> number >> name;
      queries[i].setNumber(number);
      queries[i].setName(name);
    } else {
      cin >> number;
      queries[i].setNumber(number);
    }
  }
  return queries;
}

int main() {
  DirectIndexPhoneBook book;
  auto queries = read_queries();

  for (auto q : queries) {
    if (q.type() == "add") {
      book.add(q.number(), q.name());
    }
    if (q.type() == "del") {
      book.del(q.number());
    }
    if (q.type() == "find") {
      cout << book.find(q.number()) << endl;
    }
  }
  return 0;
}
