#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

template <typename T> class DisjointSetsElement {
public:
  DisjointSetsElement(T size = 0, T parent = -1, T rank = 0)
      : m_size(size), m_parent(parent), m_rank(rank) {}

  void setParent(T p) { m_parent = p; }
  T parent() const { return m_parent; }

  void setSize(T size) { m_size = size; }
  T size() const { return m_size; }

  void setRank(T rank) { m_rank = rank; }
  T rank() const { return m_rank; }

private:
  T m_size = 0;
  T m_parent = -1;
  T m_rank = 0;
};

template <typename T> class DisjointSets {
public:
  DisjointSets() {}

  T getParent(T table) {
    if (table != m_sets[table].parent()) {
      m_sets[table].setParent(getParent(m_sets[table].parent()));
    }
    return m_sets[table].parent();
  }

  void merge(T destination, T source) {
    T realDestination = getParent(destination);
    T realSource = getParent(source);

    if (realDestination != realSource) {
      T newParent = realSource;
      T oldParent = realDestination;
      if (m_sets[realDestination].rank() >= m_sets[realSource].rank()) {
        newParent = realDestination;
        oldParent = realSource;
      }
      m_sets[oldParent].setParent(newParent);
      m_sets[oldParent].setRank(m_sets[oldParent].rank() + 1);
      m_sets[newParent].setSize(m_sets[newParent].size() +
                                m_sets[oldParent].size());
      m_max_table_size = max(m_max_table_size, m_sets[newParent].size());
    }
  }

  void addSet(T size) {
    m_sets.push_back(size);
    m_sets[m_sets.size() - 1].setParent(m_sets.size() - 1);
    m_max_table_size = max(m_max_table_size, size);
  }

  T max_table_size() const { return m_max_table_size; }

private:
  T m_size = 0;
  T m_max_table_size = 0;
  vector<DisjointSetsElement<T>> m_sets;
};

int main() {
  int n, m;

  cin >> n >> m;

  DisjointSets<int> tables;
  for (int i = 0; i < n; i++) {
    int size;
    cin >> size;
    tables.addSet(size);
  }

  for (int i = 0; i < m; i++) {
    int destination, source;
    cin >> destination >> source;
    --destination;
    --source;

    tables.merge(destination, source);
    cout << tables.max_table_size() << endl;
  }

  return 0;
}
