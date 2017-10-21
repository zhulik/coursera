#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <math.h>

using namespace std;

std::string repeat(int n, const string &a) {
    std::ostringstream os;
    for(int i = 0; i < n; i++)
        os << a;
    return os.str();
}

bool is_greater_or_equal(const string &a, const string &maxDigit) {
  return repeat(a.length(), maxDigit) <= repeat(maxDigit.length(), a);
}

string largest_number(vector<string> a) {
  stringstream ret;
  string maxDigit = a[0];
  while(a.size() > 0) {
    maxDigit = a[0];
    int maxI = 0;
    for(auto i = 0; i < a.size(); i++) {
      if (is_greater_or_equal(a[i], maxDigit) ) {
        maxDigit = a[i];
        maxI = i;
      }
    }
    ret << maxDigit;
    a.erase(a.begin() + maxI);
  }

  return ret.str();
}

void stress_test() {
  assert(is_greater_or_equal("2", "21"));
  assert(largest_number({"21","2"}) == "221");
  assert(largest_number({"9", "4", "6", "1", "9"}) == "99641");
  assert(largest_number({"23", "39", "92"}) == "923923");
  assert(largest_number({"2", "8", "2", "3", "6", "4", "1", "1", "10", "6", "3", "3", "6", "1", "3", "8", "4", "6", "1", "10", "8", "4", "10", "4", "1", "3", "2", "3", "2", "6", "1", "5", "2", "9", "8", "5", "10", "8", "7", "9", "6", "4", "2", "6", "3", "8", "8", "9", "8", "2", "9", "10", "3", "10", "7", "5", "7", "1", "7", "5", "1", "4", "7", "6", "1", "10", "5", "4", "8", "4", "2", "7", "8", "1", "1", "7", "4", "1", "1", "9", "8", "6", "5", "9", "9", "3", "7", "6", "3", "10", "8", "10", "7", "2", "5", "1", "1", "9", "9", "5"}) == "9999999998888888888887777777776666666666555555554444444443333333333222222222111111111111111101010101010101010");
}

int main() {
  // stress_test();
  int n;
  cin >> n;
  vector<string> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    cin >> a[i];
  }
  cout << largest_number(a);
}
