#ifndef LOCAL
#pragma GCC optimize("O3")
#endif

#include <bits/stdc++.h>

void solve() {
    int n, m;
    std::cin >> n >> m;
    
    std::vector<int> bytes(n), costs(n);
    for (int &i : bytes) {std::cin >> i;}
    for (int &i : costs) {std::cin >> i;}
    
    std::vector<int> dp(10001, -100000000), temp(10001);
    dp[0] = 0;
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= 10000; ++j) {
            temp[j] = dp[j];
        }
        for (int j = 0; j <= 10000; ++j) {
            temp[j + costs[i]] = std::max(temp[j + costs[i]], dp[j] + bytes[i]);
        }
        std::swap(dp, temp);
    }
    
    for (int j = 0; j <= 10000; ++j) {
        if (dp[j] >= m) {
            std::cout << j << '\n';
            break;
        }
    }
}

#ifndef LOCAL
int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
#endif