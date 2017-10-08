#include <iostream>

using namespace std;

template<typename T> T get_fibonacci_huge_fast(T n, T m) {
    auto pisano_length =  pisano_period_length(m);
    n = n % 60;
    if (n <= 1)
        return n;

    T previous = 0;
    T current  = 1;

    for (T i = 0; i < n - 1; ++i) {
        T tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current + 1)  % m;
    }

    return current % m;
}

int main() {
    long long n, m;
    cin >> n >> m;
    cout << get_fibonacci_huge_fast(n, m) << endl;
}
