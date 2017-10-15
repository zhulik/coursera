#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Item {
public:
  Item(int weight, int value) : m_weight(weight), m_value(value) {
    m_price = ((float) m_value) / m_weight;
  };

  bool operator<(const Item &other) const {
    return m_price > other.m_price;
  }

  int weight() const {
    return m_weight;
  }

  int setWeight(int w) {
    m_weight = w;
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

double get_optimal_value(int capacity, vector<Item> items) {
  double value = 0.0;

  for(int i = 0; i < items.size(); i++) {
      if ( capacity == 0 ) {
        return value;
      }
      double a = min(items[i].weight(), capacity);
      value += a*items[i].price();
      items[i].setWeight(items[i].weight() - a);
      capacity -= a;
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

  cout.precision(7);
  cout << optimal_value << endl;
  return 0;
}
