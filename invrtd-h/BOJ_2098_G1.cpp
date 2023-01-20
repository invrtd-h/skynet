#include <bits/stdc++.h>

int main() {
    int n; std::cin >> n;
    
    std::vector<std::vector<int>> adj(n, std::vector<int>(n));
    for (auto &v : adj) {
        for (int &x : v) {
            std::cin >> x;
            if (x == 0) x = 100'000'000;
        }
    }
    
    std::vector<std::vector<int>> memo(n, std::vector<int>(1 << n, -1));
    std::function<int(int, unsigned int)> dp;
    dp = [n, adj, memo, &dp](int v, unsigned int bits) mutable {
        if (memo[v][bits] != -1) return memo[v][bits];
        if ((bits & (bits - 1)) == 0) return memo[v][bits] = adj[0][v];
        
        int ret = 2'000'000'000;
        for (int w = 0; w < n; ++w) {
            if (v != w and bits & (1 << w)) {
                ret = std::min(ret, dp(w, bits & ~(1 << v)) + adj[w][v]);
            }
        }
        
        return memo[v][bits] = ret;
    };
    
    std::cout << dp(0, (1 << n) - 1) << '\n';
}