#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

template <typename T> using DVector = vector<vector<T>>;

template<typename T>
class Expression {
public:
  Expression(const string &exp):m_expression(exp) {
    string n;

    for (auto t : exp) {
      if (t == '*' || t == '+' || t == '-') {
        m_numbers.push_back(stoi(n));
        n = "";
        m_operators.push_back(t);
        continue;
      }
      n += t;
    }
    m_numbers.push_back(stoi(n));
  }

  vector<T> numbers() const { return m_numbers; }
  vector<char> operators() const { return m_operators; }

private:
  string m_expression;
  vector<T> m_numbers;
  vector<char> m_operators;

};

template<typename T> T eval(T a, T b, char op) {
  if (op == '*') {
    return a * b;
  } else if (op == '+') {
    return a + b;
  } else if (op == '-') {
    return a - b;
  } else {
    assert(0);
  }
}

template<typename T> void print(const vector<T> &row) {
  for(auto item: row) {
    cout << item << " ";
  }
  cout << endl;
}

template<typename T> void print(const DVector<T> &tries) {
  for(auto row: tries) {
    for(auto item: row) {
      cout << item << " ";
    }
    cout << endl;
  }
}

template<typename T>
pair<T, T> min_and_max(const Expression<T> &e, const DVector<T> &m, const DVector<T> &M, int i, int j) {
  T mn = numeric_limits<T>::max();
  T mx = -numeric_limits<T>::max();
  for (int k = i; k < j; k++) {
      T a = eval(M[i][k], M[k+1][j], e.operators()[k]);
      T b = eval(M[i][k], m[k+1][j], e.operators()[k]);
      T c = eval(m[i][k], M[k+1][j], e.operators()[k]);
      T d = eval(m[i][k], m[k+1][j], e.operators()[k]);
      mn = min({mn, a, b, c, d});
      mx = max({mx, a, b, c, d});
  }
  return pair<T, T>(mn, mx);
}

template<typename T>
T get_maximum_value(const Expression<T> &e) {
  auto n = e.numbers().size();
  DVector<T> mins(n, vector<T>(n, 0));
  DVector<T> maxs(n, vector<T>(n, 0));
  for(int i = 0; i < e.numbers().size(); i++) {
    mins[i][i] = e.numbers()[i];
    maxs[i][i] = e.numbers()[i];
  }
  for(int s = 0; s < n; s++) {
    for(int i = 0; i < n - s; i++) {
      int j = i + s;
      if (i == j)
        continue;
      auto p = min_and_max(e, mins, maxs, i, j);
      mins[i][j] = p.first;
      maxs[i][j] = p.second;
    }
  }
  return maxs[0][n-1];
}

int main() {
  string s;
  cin >> s;
  cout << get_maximum_value(Expression<long long>(s)) << endl;
}
