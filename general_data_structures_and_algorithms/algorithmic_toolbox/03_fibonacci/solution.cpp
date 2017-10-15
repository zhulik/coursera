#include <iostream>
#include <vector>

using namespace std;

int fibonacci_fast(int n) {
    vector<unsigned long long int> cache(n+1, 0);
    cache[0] = 0;
    cache[1] = 1;
    for(int i = 2; i<= n; i++) {
      cache[i] = cache[i-1] + cache[i-2];
    }
    return cache[n];
}

int main() {
    int n = 0;
    std::cin >> n;
    // test_solution();

    // std::cout << fibonacci_naive(n) << '\n';
    //test_solution();
    std::cout << fibonacci_fast(n) << '\n';
    return 0;
}
