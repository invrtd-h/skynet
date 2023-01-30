#ifndef LOCAL
#pragma GCC optimize("O3")
#endif

#include <bits/stdc++.h>

constexpr int NIL = -100'000'000;

auto next(unsigned int bits, int J) {
    std::vector<unsigned int> ret(1, 0);
    for (int bi = 0; bi < J; ++bi) {
        const int SZ = ret.size();
        for (int i = 0; i < SZ; ++i) {
            unsigned int x = ret[i] | (1 << bi);
            if (x & bits) {continue;}
            if (ret[i] & (1 << (bi - 1))) {continue;}
            ret.push_back(x);
        }
    }
    
    return ret;
}

void solve() {
    int I, J, K;
    std::cin >> I >> J >> K;
    
    std::vector grid(I, std::vector<int>(J));
    for (auto &v : grid) {
        for (int &i : v) {
            std::cin >> i;
        }
    }
    
    auto get_sum = [&grid, J](int i, unsigned int bits) {
        int ret = 0;
        for (int b = 0; b < J; ++b) {
            if (bits & (1 << b)) {
                ret += grid[i][b];
            }
        }
        return ret;
    };
    
    std::vector nexts_vec(1 << J, std::vector<unsigned int>());
    for (unsigned int b = 0; b < (1 << J); ++b) {
        nexts_vec[b] = next(b, J);
    }
    
    std::vector dp(1 << J, std::vector<int>(K + 1, NIL));
    auto temp = dp;
    
    const auto &next_0 = nexts_vec[0];
    for (unsigned int bits : next_0) {
        dp[bits][std::popcount(bits)] = get_sum(0, bits);
    }
    
    for (int i = 1; i < I; ++i) {
        temp = dp;
        
        for (unsigned int bits = 0; bits < (1 << J); ++bits) {
            const auto &nexts = nexts_vec[bits];
            for (int k = 0; k <= K; ++k) {
                if (dp[bits][k] == NIL) {continue;}
                
                for (unsigned int next_bits : nexts) {
                    int next_bitcount = k + std::popcount(next_bits);
                    if (next_bitcount > K) {continue;}
                    
                    temp[next_bits][next_bitcount] =
                            std::max(temp[next_bits][next_bitcount],
                                     dp[bits][k] + get_sum(i, next_bits));
                }
            }
        }
        
        std::swap(temp, dp);
    }
    
    int ret = NIL;
    for (const auto &v : dp) {
        ret = std::max(ret, v[K]);
    }
    std::cout << ret << '\n';
}

#ifndef LOCAL
int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
#endif