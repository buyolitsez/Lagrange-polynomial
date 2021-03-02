#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

typedef ll T;

const T EPS = 1e-9;

bool IsInteger() {
    return (typeid(T) != typeid(double)) && (typeid(T) != typeid(float)) && (typeid(T) != typeid(long double));
}

bool IsEqual(T a, T b) {
    return abs(a - b) <= EPS;
}

pair<T, T> Add(pair <T, T> a, pair <T, T> b) {
    return {a.first * b.second + b.first * a.second, a.second * b.second};
}

pair<T, T> Mul(pair <T, T> a, pair <T, T> b) {
    return {a.first * b.first, a.second * b.second};
}

struct Polynom{
    vector<pair<T,T>> a;
    int n;
    Polynom() {
        n = 0;
        a = {};
    }
    Polynom(int nn) {
        n = nn;
        a.resize(n, pair<T, T>{0, 1});
    }
    Polynom(int nn, const vector<pair<T,T>>& aa) {
        n = nn;
        a = aa;
    }
    void Correct() {
        while (n > 1 && IsEqual(a.back().first, 0)) {
            a.pop_back();
            --n;
        }
        for (auto &[x, y] : a) {
            if (IsEqual(x, 0)) {
                x = 0;
                y = 1;
                continue;
            }
            if (IsInteger) {
                int g = __gcd((ll)x, (ll)y);
                x = x / g;
                y = y / g;
            }
            if (y < 0) {
                x *= -1;
                y *= -1;
            }
        }
    }
    Polynom operator+(const Polynom& p) {
        Polynom ans(max(n, p.n));
        for (int i = 0; i < ans.n; ++i) {
            if (i < n) {
                ans.a[i] = Add(ans.a[i], a[i]);
            }
            if (i < p.n) {
                ans.a[i] = Add(ans.a[i], p.a[i]);
            }
        }
        ans.Correct();
        return ans;
    }
    Polynom operator*(const Polynom& p) {
        Polynom ans(n + p.n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < p.n; ++j) {
                ans.a[i + j] = Add(ans.a[i + j], Mul(a[i], p.a[j]));
            }
        }
        ans.Correct();
        return ans;
    }
};

Polynom Interpolation(const vector <pair<T, T>>& coord) {
    int n = (int)coord.size();
    Polynom ans;
    for (int i = 0; i < n; ++i) {
        Polynom mul(1);
        mul.a[0] = {1, 1};
        for (int j = 0; j < n; ++j) {
            if (i == j) {continue;}
            T del = (coord[i].first - coord[j].first);
            Polynom res = Polynom(2, vector<pair<T,T>>{pair<T,T>{-coord[j].first, del}, pair<T,T>{1, del}});
            mul = mul * res;
        }
        mul = mul * Polynom(1, {{coord[i].second, 1}});
        ans = ans + mul;
    }
    return ans;
}

void Solve() {
    int n;
    cin >> n;
    vector <pair <T, T>> a(n);
    for (auto &[x, y] : a) {
        cin >> x >> y;
    }
    Polynom ans = Interpolation(a);
    for (int i = 0; i < ans.n; ++i) {
        if (IsInteger()) {
            cout << ans.a[i].first << ' ' << ans.a[i].second << '\n';
        } else {
            cout << setprecision(5) << fixed;
            cout << ans.a[i].first / ans.a[i].second << '\n';
        }
    }
}

signed main() {
    Solve();
    return 0;
}
