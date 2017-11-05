#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<typename T> void print(const vector<vector<T>> &tries) {
  for(auto row: tries) {
    for(auto item: row) {
      cout << item << " ";
    }
    cout << endl;
  }
}

template<typename T> T min(T i, T j, T k) {
  return min(i, std::min(j, k));
}

int edit_distance(const string &str1, const string &str2) {
  vector<vector<int>> tries(str1.length() + 1, vector<int>(str2.length() + 1, 0));
  for (int i = 0; i <= str1.length(); i++) {
    tries[i][0] = i;
  }
  for (int j = 0; j <= str2.length(); j++) {
    tries[0][j] = j;
  }

  for (int i = 1; i <= str1.length(); i++) {
    for (int j = 1; j <= str2.length(); j++) {
      int ins = tries[i][j-1] + 1;
      int del = tries[i-1][j] + 1;
      int mat = tries[i-1][j-1];
      int mis = tries[i-1][j-1] + 1;

      if (str1[i-1] == str2[j-1]) {
        tries[i][j] = min(ins, del, mat);
      } else {
        tries[i][j] = min(ins, del, mis);
      }
    }
  }


  return tries[str1.length()][str2.length()];
}

int main() {
  string str1;
  string str2;
  cin >> str1 >> str2;
  cout << edit_distance(str1, str2) << endl;
  return 0;
}
