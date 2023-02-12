#include <bits/stdc++.h>

constexpr int MAX_SZ = 320;

class Matrix {
public:
    using data_type = std::vector<std::bitset<MAX_SZ>>;
    
    data_type data;
    int I, J;
    
    explicit Matrix(std::vector<std::string> vs)
            : I(static_cast<int>(vs.size())),
              J(static_cast<int>(vs.size())),
              data(static_cast<int>(vs.size()))
    {
        for (int i = 0; i < I; ++i) {
            for (int j = 0; j < J; ++j) {
                data[i][j] = (vs[i][j] == '1');
            }
        }
    }
    
    Matrix(int I, int J) : I(I), J(J), data(I) {}
    
    void row_elimination(int from, int to) {
        if (from == to) {return;}
        data[to] ^= data[from];
    }
    
    void row_swap(int from, int to) {
        if (from == to) {return;}
        std::swap(data[from], data[to]);
    }
    
    void column_elimination(int from, int to) {
        if (from == to) {return;}
        for (int i = 0; i < I; ++i) {
            data[i][to] = data[i][to] ^ data[i][from];
        }
    }
    
    void column_swap(int from, int to) {
        if (from == to) {return;}
        for (int i = 0; i < I; ++i) {
            bool b = data[i][from];
            data[i][from] = data[i][to];
            data[i][to] = b;
        }
    }
    
    bool reduce() {
        bool ret = data[I - 1][J - 1];
        data.pop_back();
        return ret;
    }
    
    [[nodiscard]] auto get_transpose() const {
        auto ret = Matrix(J, I);
        for (int i = 0; i < I; ++i) {
            for (int j = 0; j < J; ++j) {
                ret.data[j][i] = data[i][j];
            }
        }
        return ret;
    }
    
    [[nodiscard]] int get_first_nonzero_under(int i, int j) const {
        for (int i1 = i; i1 < I; ++i1) {
            if (data[i1][j]) {
                return i1;
            }
        }
        return -1;
    }
    
    [[nodiscard]] int get_first_nonzero_right(int i, int j) const {
        for (int j1 = j; j1 < J; ++j1) {
            if (data[i][j1]) {
                return j1;
            }
        }
        return -1;
    }
    
    [[nodiscard]] Matrix principal_minor() const {
        Matrix ret = *this;
        
        ret.data.erase(ret.data.begin());
        --ret.I;
        
        for (auto &bs : ret.data) {
            bs >>= 1;
        }
        --ret.J;
        
        return ret;
    }
    
    [[nodiscard]] Matrix principal_r() const {
        auto ret = Matrix(1, J - 1);
        ret.data[0] = data[0] >> 1;
        
        return ret;
    }
    
    [[nodiscard]] Matrix principal_c() const {
        auto ret = Matrix(I - 1, 1);
        for (int i = 0; i < I - 1; ++i) {
            ret.data[i][0] = data[i + 1][0];
        }
        
        return ret;
    }
    
    [[nodiscard]] bool a_00() const {
        return data[0][0];
    }
    
    [[nodiscard]] Matrix toepliz() const {
        assert(I == J);
        
        bool a = a_00();
        Matrix r = principal_r();
        Matrix c = principal_c();
        Matrix m = principal_minor();
        
        Matrix ret(I + 1, J);
        for (int i = 0; i < I; ++i) {
            ret.data[i][i] = true;
            ret.data[i + 1][i] = a;
        }
        
        for (int k = 2; k < I + 1; ++k) {
            bool t = (r * c).a_00();
            if (t) {
                for (int i = 0; i + k < I + 1; ++i) {
                    ret.data[i + k][i] = true;
                }
            }
            c = m * c;
        }
        
        return ret;
    }
    
    [[nodiscard]] Matrix get_cp() const {
        assert(I == J);
        
        if (I == 1) {
            Matrix ret = Matrix(2, 1);
            ret.data[0][0] = true;
            ret.data[1][0] = data[0][0];
            
            return ret;
        }
        
        return toepliz() * principal_minor().get_cp();
    }
    
    friend auto operator*(const Matrix &l, const Matrix &r) -> Matrix {
        assert(l.J == r.I);
        auto ret = Matrix(l.I, r.J);
        
        auto r_tp = r.get_transpose();
        for (int i = 0; i < l.I; ++i) {
            for (int j = 0; j < r.J; ++j) {
                ret.data[i][j] = (l.data[i] & r_tp.data[j]).count() % 2;
            }
        }
        
        return ret;
    }
    
    friend auto operator<<(std::ostream &os, const Matrix &r) -> std::ostream & {
        for (int i = 0; i < r.I; ++i) {
            for (int j = 0; j < r.J; ++j) {
                os << r.data[i][j];
            } os << '\n';
        }
        return os;
    }
};

class BitMatrix {
public:
    Matrix a, b;
    int size;
    
    BitMatrix(std::vector<std::string> vsa, std::vector<std::string> vsb)
            : a(std::move(vsa)), b(std::move(vsb)) {
        size = a.I;
    }
    
    void row_elimination(int from, int to) {
        a.row_elimination(from, to);
        b.row_elimination(from, to);
    }
    
    void row_swap(int from, int to) {
        a.row_swap(from, to);
        b.row_swap(from, to);
    }
    
    void column_elimination(int from, int to) {
        a.column_elimination(from, to);
        b.column_elimination(from, to);
    }
    
    void column_swap(int from, int to) {
        a.column_swap(from, to);
        b.column_swap(from, to);
    }
    
    bool a_triangularize() {
        int i = 0, j = 0;
        while (i < size and j < size) {
            int i1 = a.get_first_nonzero_under(i, j);
            if (i1 == -1) {
                ++j;
                continue;
            }
            row_swap(i, i1);
            
            for (int i2 = i + 1; i2 < size; ++i2) {
                if (a.data[i2][j]) {
                    row_elimination(i, i2);
                }
            }
            ++i;
            ++j;
        }
        return a.data[size - 1][size - 1];
    }
    
    void a_identify() {
        for (int i = size - 1; i >= 0; --i) {
            for (int i2 = i - 1; i2 >= 0; --i2) {
                if (a.data[i2][i]) {
                    row_elimination(i, i2);
                }
            }
        }
    }
    
    bool b_last_row_eliminate() {
        int j_target = b.get_first_nonzero_right(size - 1, 0);
        if (j_target == -1) {return false;}
        
        column_swap(j_target, size - 1);
        
        for (int j = 0; j < size - 1; ++j) {
            if (b.data[size - 1][j]) {
                column_elimination(size - 1, j);
            }
        }
        
        a.data.pop_back();
        b.data.pop_back();
        --a.I;
        --a.J;
        --b.I;
        --b.J;
        --size;
        
        return true;
    }
    
    Matrix get_ans() {
        while (true) {
            bool temp = a_triangularize();
            if (temp) {
                a_identify();
                return b.get_cp().get_transpose();
            }
            temp = b_last_row_eliminate();
            if (not temp) {
                return Matrix(1, 1);
            }
            if (not size) {
                auto ret = Matrix(1, 1);
                ret.data[0][0] = true;
                return ret;
            }
        }
    }
    
    friend auto operator<<(std::ostream &os, const BitMatrix &r) -> std::ostream & {
        os << r.a << r.b;
        return os;
    }
};

void solve() {
    int n; std::cin >> n;
    std::vector<std::string> a(n), b(n);
    for (std::string &s : a) {std::cin >> s;}
    for (std::string &s : b) {std::cin >> s;}
    
    BitMatrix bitm(std::move(a), std::move(b));
    auto ret = bitm.get_ans();
    
    std::vector<int> vec(ret.J);
    for (int i = 0; i < ret.J; ++i) {
        vec[i] = ret.data[0][i];
    }
    std::reverse(vec.begin(), vec.end());
    vec.resize(n + 1, 0);
    
    for (int i : vec) {
        std::cout << i << '\n';
    }
}

#ifndef LOCAL
int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
#endif