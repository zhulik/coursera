#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

template<typename T>
vector<T> greedy_sequence(T n) {
  vector<T> sequence;
  while (n >= 1) {
    sequence.push_back(n);
    if (n % 3 == 0) {
      n /= 3;
    } else if (n % 2 == 0) {
      n /= 2;
    } else {
      n -= 1;
    }
  }
  reverse(sequence.begin(), sequence.end());
  return sequence;
}

template<typename T>
vector<T> optimal_sequence(T n) {
  vector<T> tries(n + 1, 0);
  vector<T> steps(n + 1, 0);
  tries[1] = 0;
  tries[2] = 1;
  tries[3] = 1;
  for(T i = 4; i <= n; i++) {
    T min = std::numeric_limits<T>::max();
    T step = 0;

    if (i % 3 == 0) {
      if (tries[i / 3] < min) {
        min = tries[i / 3];
        step = i / 3;
      }
    } else if (i % 2 == 0) {
      if (tries[i / 2] < min) {
        min = tries[i / 2];
        step = i / 2;
      }
    }
    if (tries[i - 1] < min && tries[i - 1] > 0) {
      min = tries[i - 1];
      step = i - 1;
    }

    tries[i] = min + 1;
    steps[i] = step;
  }

  vector<T> sequence;

  T i = n;
  while(i >= 1) {
    sequence.push_back(i);
    i = steps[i];
  }

  if (sequence.size() > 1)
    sequence.push_back(1);

  reverse(sequence.begin(), sequence.end());

  return sequence;
}

int main() {
  int n;
  cin >> n;
  vector<int> sequence = optimal_sequence(n);
  cout << sequence.size() - 1 << endl;
  for (size_t i = 0; i < sequence.size(); ++i) {
    cout << sequence[i] << " ";
  }
}
