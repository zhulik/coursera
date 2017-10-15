#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Item {
public:
  Item(int weight, int value) : m_weight(weight), m_value(value) {
    m_price = ((float) m_value) / m_weight;
  };

  bool operator<(Item other) {
    return m_price > other.m_price;
  }

  int weight() const {
    return m_weight;
  }

  int value() const {
    return m_value;
  }

  double price() const {
    return m_price;
  }

private:
  int m_weight = 0;
  int m_value = 0;
  double m_price = 0;
};

double get_optimal_value(int capacity, const vector<Item> &items) {
  double value = 0.0;

  while(capacity > items.front().weight()) {
    for(auto item: items) {
      if (capacity >= item.weight()) {
        capacity -= item.weight();
        value += item.value();
      }
    }
  }

  if (capacity > 0) {
    value += items.front().price() * capacity;
  }

  return value;
}

int main() {
  int n;
  int capacity;
  cin >> n >> capacity;
  std::vector<Item> items;
  for (int i = 0; i < n; i++) {
    int w, v;
    cin >> v >> w;
    items.push_back(Item(w, v));
  }

  sort(items.begin(), items.end());

  double optimal_value = get_optimal_value(capacity, items);

  cout.precision(10);
  cout << optimal_value << endl;
  return 0;
}
