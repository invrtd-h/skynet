#include<bits/stdc++.h>

using namespace std;

class Modulo {
    static const int DIV = 998244353;
public:
    long long int n;
    Modulo() {}
    Modulo(long long int _n) {
        if (_n >= 0) {
            n = _n % DIV;
        } else {
            n = _n % DIV;
            n += DIV;
        }
    }
    Modulo(const Modulo& m) : n(m.n) {}
    Modulo& operator=(const Modulo& rhs) {n = rhs.n; return *this;}
    Modulo& operator=(const long long int n) {*this = Modulo(n); return *this;}
    Modulo operator+(const Modulo& rhs) const {return Modulo((n + rhs.n) % DIV);}
    Modulo& operator+=(const Modulo& rhs) {*this = *this + rhs; return *this;}
    Modulo operator-() const {return n == 0 ? Modulo(0) : Modulo(DIV - n);}
    Modulo operator-(const Modulo& rhs) const {return *this + (-rhs);}
    Modulo& operator-=(const Modulo& rhs) {(*this) = (*this) - rhs; return *this;}
    Modulo operator*(const Modulo& rhs) const {return Modulo((n * rhs.n) % DIV);}
    Modulo& operator*=(const Modulo& rhs) {(*this) = (*this) * rhs; return *this;}
    
    Modulo pow(unsigned long long int powered) const {
        if (powered == 0) {
            return Modulo(1);
        } else if (powered == 1) {
            return *this;
        }
        Modulo hold = pow(powered / 2);
        if (powered % 2 == 0) {
            return hold * hold;
        } else {
            return hold * hold * (*this);
        }
    }
    Modulo inverse() const {return this->pow(DIV - 2);}
    Modulo operator/(const Modulo& rhs) const {
        if (rhs == 0) {
            throw "DIVISION BY 0";
        }
        return *this * rhs.inverse();
    }
    Modulo& operator/=(const Modulo& rhs) {*this = *this / rhs; return *this;}
    bool operator==(const Modulo& rhs) const {return n == rhs.n;}
    bool operator!=(const Modulo& rhs) const {return n != rhs.n;}
    int to_int() const {return (int) this->n;}
    int to_int_moderate() const {
        return n * n < (n - DIV) * (n - DIV) ? (int) n : (int) (n - DIV);
    }
    
    friend ostream& operator<<(ostream& os, const Modulo& m);
};

ostream& operator<<(ostream& os, const Modulo& m) {
    os << m.to_int();
    return os;
}

template<class Type>
class Polynomial {
    Type* p;
    int size;
public:
    explicit Polynomial(Type* t, int deg) : size(deg + 1) {
        p = new Type[deg + 1];
        for (int i = 0; i <= deg; ++i) {
            p[i] = t[i];
        }
    }
    Polynomial() : size(1) {
        p = new Type[1];
        p[0] = 1;
    }
private:
    explicit Polynomial(int _size) : size(_size) {
        p = new Type[_size];
    }
public:
    Polynomial(const Polynomial& rhs) : size(rhs.size) {
        p = new Type[rhs.size];
        for (int i = 0; i < rhs.size; ++i) {
            p[i] = rhs.p[i];
        }
    }
    Polynomial(Polynomial&& rhs) noexcept : size(rhs.size) {
            p = rhs.p;
            rhs.p = NULL;
    }
    Polynomial& operator=(const Polynomial& rhs) {
        if (p) {
            delete[] p;
        }
        
        size = rhs.size;
        p = new Type[rhs.size];
        for (int i = 0; i < rhs.size; ++i) {
            p[i] = rhs.p[i];
        }
        
        return *this;
    }
    Polynomial& operator=(Polynomial&& rhs) {
        if (p) {
            delete[] p;
        }
        size = rhs.size;
        p = rhs.p;
        rhs.p = NULL;
        
        return *this;
    }
    ~Polynomial() {
        if (p) {
            delete[] p;
        }
    }
    
    Type operator()(const Type& x) const {
        Type a = 1, ret = 0;
        for (int i = 0; i < size; ++i) {
            ret += p[i] * a;
            a *= x;
        }
        
        return ret;
    }
    
    Polynomial operator+(const Polynomial& rhs) const {
        if (size < rhs.size) {
            Polynomial temp(rhs.size);
            for (int i = 0; i < size; ++i) {
                temp.p[i] = p[i] + rhs.p[i];
            }
            for (int i = size; i < rhs.size; ++i) {
                temp.p[i] = rhs.p[i];
            }
            temp.resize();
            return temp;
        } else {
            Polynomial temp(size);
            for (int i = 0; i < rhs.size; ++i) {
                temp.p[i] = p[i] + rhs.p[i];
            }
            for (int i = rhs.size; i < size; ++i) {
                temp.p[i] = p[i];
            }
            temp.resize();
            return temp;
        }
    }
    Polynomial& operator+=(const Polynomial& rhs) {
        *this = *this + rhs;
        return *this;
    }
    
    Polynomial operator*(const Type& k) const {
        Polynomial temp(*this);
        temp *= k; return temp;
    }
    Polynomial& operator*=(const Type& k) {
        for (int i = 0; i < size; ++i) {
            p[i] *= k;
        }
        
        return *this;
    }
    Polynomial operator*(const Polynomial& rhs) const {
        Polynomial temp(size + rhs.size - 1);
        for (int i = 0; i < temp.size; ++i) {
            temp.p[i] = 0;
        }
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < rhs.size; ++j) {
                temp.p[i + j] += p[i] * rhs.p[j];
            }
        }
        
        return temp;
    }
    Polynomial& operator*=(const Polynomial& rhs) {
        *this = *this * rhs;
        return *this;
    }
    
    Polynomial operator/(const Type& k) const {
        Polynomial temp(*this);
        temp /= k; return temp;
    }
    Polynomial& operator/=(const Type& k) {
        for (int i = 0; i < size; ++i) {
            p[i] /= k;
        }
        
        return *this;
    }
    
    
    Polynomial synthetic_div(const Type& rhs) const {
        if (size == 1) {
            Polynomial ret(1);
            ret.p[0] = 0;
            return ret;
        }
        Polynomial temp(size - 1);
        temp.p[size - 2] = p[size - 1];
        for (int i = size - 2; i > 0; --i) {
            temp.p[i - 1] = p[i] + temp.p[i] * rhs;
        }
        
        return temp;
    }
    Polynomial& apply_synthetic_div(const Type& rhs) {
        *this = this->synthetic_div(rhs);
        return *this;
    }
    
    int degree() const {
        return size - 1;
    }
    
    const Polynomial& print() const {
        if (size == 0) {
            cout << "null polynomial" << endl;
        } else {
            cout << p[0];
            for (int i = 1; i < size; ++i) {
                cout << " + " << p[i] << 'x' << i;
            } cout << endl;
        }
        
        return *this;
    }
    
    static Polynomial get_linear(const Type& t) {
        Type arr[2];
        arr[0] = -t; arr[1] = 1;
        return Polynomial<Type>(arr, 1);
    }

private:
    Polynomial& resize() {
        while (p[size - 1] == 0 && size > 1) {
            --size;
        }
        
        return *this;
    }
};

template<class Type>
Polynomial<Type> products(Type* arr, int size) {
    Polynomial<Type> ret;
    for_each(arr, arr + size, [&ret](const Type& r){ret *= Polynomial<Type>::get_linear(r);});
    
    return ret;
}

template<class Type>
Type coeffs(Type* x, int size, int i) {
    Type ret = 1, missed = x[i];
    for_each(x, x + size, [&ret, missed](const Type& r){ret *= (r == missed ? 1 : missed - r);});
    
    return ret;
}

template<class Type>
Polynomial<Type> lag_interpol(Type* x, Type* y, int size) {
    const Polynomial<Type> product = products(x, size);
    
    Polynomial<Type> ret = product.synthetic_div(x[0]) * (y[0] / coeffs(x, size, 0));
    for (int i = 1; i < size; ++i) {
        ret += product.synthetic_div(x[i]) * (y[i] / coeffs(x, size, i));
    }
    
    return ret;
}

template<class Type>
class Matrix {
private:
    Type** p;
    unsigned int n; // size

public:
    
    explicit Matrix(int _n) : n(_n) {
        this->init();
    }
    
    ~Matrix() {
        if (p) {
            for (int i = 0; i < n; ++i) {
                delete[] p[i];
            }
            delete[] p;
        }
    }
    
    Matrix(const Matrix& rhs) : n(rhs.n) {
        this->init();
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                p[i][j] = rhs.p[i][j];
            }
        }
    }
    
    Matrix(Matrix&& rhs) noexcept : n(rhs.n) {
            p = rhs.p;
            rhs.p = NULL;
    }
    
    Matrix& operator=(const Matrix& rhs) {
        if (p) {
            for (int i = 0; i < n; ++i) {
                delete[] p[i];
            }
            delete[] p;
        }
        
        n = rhs.n;
        this->init();
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                p[i][j] = rhs.p[i][j];
            }
        }
        
        return *this;
    }
    
    Matrix& operator=(Matrix&& rhs) {
        if (p) {
            for (int i = 0; i < n; ++i) {
                delete[] p[i];
            }
            delete[] p;
        }
        
        n = rhs.n;
        p = rhs.p;
        rhs.p = NULL;
        
        return *this;
    }

private:
    void init() {
        p = new Type*[n];
        for (int i = 0; i < n; ++i) {
            p[i] = new Type[n];
            for (int j = 0; j < n; ++j) {
                p[i][j] = 0;
            }
        }
    }

public:
    Matrix& put(Type n, int i, int j) {
        p[i][j] = n;
        
        return *this;
    }
    
    Matrix operator+(const Matrix& rhs) const {
        if (n != rhs.n) {
            throw "NO CORRECT SIZE ERROR";
        } else {
            Matrix hold(*this);
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    hold.p[i][j] += rhs.p[i][j];
                }
            }
            return hold;
        }
    }
    
    Matrix& operator+=(const Matrix& rhs) {
        if (n != rhs.n) {
            throw "NO CORRECT SIZE ERROR";
        } else {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    p[i][j] += rhs.p[i][j];
                }
            }
            return *this;
        }
    }
    
    Matrix operator-(const Matrix& rhs) const {
        if (n != rhs.n) {
            throw "NO CORRECT SIZE ERROR";
        } else {
            Matrix hold(*this);
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    hold.p[i][j] -= rhs.p[i][j];
                }
            }
            return hold;
        }
    }
    
    Matrix& operator-=(const Matrix& rhs) {
        if (n != rhs.n) {
            throw "NO CORRECT SIZE ERROR";
        } else {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    p[i][j] -= rhs.p[i][j];
                }
            }
            return *this;
        }
    }
    
    Matrix operator*(Type k) const {
        Matrix hold(*this);
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                hold.p[i][j] *= k;
            }
        }
        
        return hold;
    }
    
    Matrix& operator*=(Type k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                p[i][j] *= k;
            }
        }
        
        return *this;
    }
    
    Matrix operator*(const Matrix& rhs) const {
        if (n != rhs.n) {
            throw "NO CORRECT SIZE ERROR";
        } else {
            Matrix hold(n);
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    for (int k = 0; k < n; ++k) {
                        hold.p[i][j] += p[i][k] * rhs.p[k][j];
                    }
                }
            }
            
            return hold;
        }
    }
    
    Matrix& operator*=(const Matrix& rhs) {
        if (n != rhs.n) {
            throw "NO CORRECT SIZE ERROR";
        } else {
            *this = *this * rhs;
            return *this;
        }
    }
    
    Matrix& exchange(Matrix& rhs) {
        swap(n, rhs.n);
        swap(p, rhs.p);
        
        return *this;
    }
    
    Matrix& substract_identity(Type rhs) {
        for (int i = 0; i < n; ++i) {
            p[i][i] -= rhs;
        }
        
        return *this;
    }
    
    const Matrix& print() const {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << p[i][j] << ' ';
            } cout << '\n';
        }
        return *this;
    }
    
    Matrix& print() {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << p[i][j] << ' ';
            } cout << '\n';
        }
        return *this;
    }
    
    
    Matrix& elem1_row(int r, Type k, int first_nonzero_idx = 0) {
        for (int j = first_nonzero_idx; j < n; ++j) {
            p[r][j] *= k;
        }
        return *this;
    }
    Matrix& elem1_col(int c, Type k, int first_nonzero_idx = 0) {
        for (int i = first_nonzero_idx; i < n; ++i) {
            p[i][c] *= k;
        }
        return *this;
    }
    Matrix& elem2_row(int r1, int r2) {
        Type* hold = p[r1];
        p[r1] = p[r2];
        p[r2] = hold;
        return *this;
    }
    Matrix& elem2_col(int c1, int c2) {
        Type hold;
        for (int i = 0; i < n; ++i) {
            hold = p[i][c1];
            p[i][c1] = p[i][c2];
            p[i][c2] = hold;
        }
        return *this;
    }
    Matrix& elem3_row(int from, int to, Type k, int first_nonzero_idx = 0) {
        for (int j = first_nonzero_idx; j < n; ++j) {
            p[to][j] += p[from][j] * k;
        }
        return *this;
    }
    Matrix& elem3_col(int from, int to, Type k, int first_nonzero_idx = 0) {
        for (int i = first_nonzero_idx; i < n; ++i) {
            p[i][to] += p[i][from] * k;
        }
        return *this;
    }
    
    Matrix& hsfy() {
        for (int i = 1; i < n; ++i) {
            // find the first nonzero term under matrix[i][i - 1]
            int t = i;
            for (; t < n && p[t][i - 1] == 0; ++t) {}
            
            if (t == n) {
                // do nothing about this column
                continue;
            } else if (t != i) {
                elem2_row(i, t);
                elem2_col(i, t);
            }
            for (int j = i + 1; j < n; ++j) {
                Type coeff = p[j][i - 1] / p[i][i - 1];
                elem3_row(i, j, -coeff);
                elem3_col(j, i, coeff);
            }
        }
        
        return *this;
    }
    
    Type det_of_hs_mtrx() const {
        Matrix temp(*this);
        Type det_so_far = 1;
        
        for (int i = 0; i < n - 1; ++i) {
            if (temp.p[i][i] != 0) {
                temp.elem3_row(i, i + 1, -temp.p[i + 1][i] / temp.p[i][i]);
                det_so_far *= temp.p[i][i];
            } else if (temp.p[i + 1][i] != 0) {
                det_so_far *= -temp.p[i + 1][i];
                temp.elem2_row(i, i + 1);
            } else {
                return 0;
            }
        }
        
        return det_so_far * temp.p[n - 1][n - 1];
    }
    
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    try {
        int n, q;
        cin >> n >> q;
        
        Matrix<Modulo> mat(n);
        int temp;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> temp;
                mat.put(temp, i, j);
            }
        }
        
        int queries[q];
        for (int i = 0; i < q; ++i) {
            cin >> queries[i];
        }
        // input end
        
        mat.hsfy();
        
        Modulo x[n + 1], y[n + 1];
        for (int i = 0; i < n + 1; ++i) {
            x[i] = i + 1;
            y[i] = mat.substract_identity(1).det_of_hs_mtrx();
        }
        
        Polynomial<Modulo> char_poly = lag_interpol(x, y, n + 1);
        
        for (int x : queries) {
            cout << char_poly(x) << ' ';
        } cout << endl;
        
    } catch (const string& str) {
        cout << str << endl;
    }
}