#include <bits/stdc++.h>
using namespace std;

template <long long M>
class mint {
private:
    long long val;
public:
    mint(long long _val = 0) : val(_val) {
        if (val < 0) val += M;
        val = val % M;
    }

    mint modpow(const mint& a, long long pow) const {
        mint num(a), res(1);
        for (;pow > 0; num = num * num, pow >>= 1) if (pow & 1) {
                res = res * num;
        }
        return res;
    }

    mint operator+(const mint& other) const {
        return mint(val + other.val);
    }

    mint operator-(const mint& other) const {
        return mint(val - other.val);
    }

    mint operator*(const mint& other) const {
        return mint(val * other.val);
    }

    mint operator/(const mint& other) const {
        return mint(val * modpow(other, M - 2).val); // FLT
    }

    friend ostream& operator<<(ostream& os, const mint& mint) {
        os << mint.val;
        return os;
    }
};

int main() {

    mint<7> x(4), y(5);

    cout << x + y << endl;
    cout << x - y << endl;
    cout << x * y << endl;
    cout << x / y << endl;

    return 0;
}