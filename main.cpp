#include <bits/stdc++.h>
#include <immintrin.h>

using namespace std;

//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")


template<typename T>
istream &operator>>(istream &in, vector<T> &a) {
    for (auto &i : a)
        in >> i;
    return in;
}

template<typename T>
ostream &operator<<(ostream &out, const vector<T> &a) {
    for (auto &i : a) {
        out << i << " ";
    }
    return out;
}

template<typename T, typename D>
istream &operator>>(istream &in, pair<T, D> &a) {
    in >> a.first >> a.second;
    return in;
}

template<typename T, typename D>
ostream &operator<<(ostream &out, const pair<T, D> &a) {
    out << a.first << " " << a.second;
    return out;
}

struct LogOutput {
    template<typename T>
    LogOutput &operator<<(const T &x) {
#ifdef DIVAN
        cout << x;
#endif
        return *this;
    }
} dout, fout;

typedef long long ll;
typedef unsigned long long ull;
typedef double dl;
typedef complex<double> cd;

#define nl '\n'
#define elif else if
#define all(_v) _v.begin(), _v.end()
#define rall(v) v.rbegin(), v.rend()
#define sz(v) (int)(v.size())
#define sqr(_v) ((_v) * (_v))
#define vpi vector<pair<int, int>>
#define eb emplace_back
#define pb push_back
#define mod(x, m) ((x) >= 0 ? ((x) % m) : ((((x) % m) + m) % m))
#define vi vector<int>
#define pi pair<int, int>
#define ti tuple<int, int, int>
#define minq(x, y) x = min((x), (y))
#define maxq(x, y) x = max(x, (y))
#define forn(i, n) for (int i = 0; i < (n); ++i)

const ll INFL = 9187201950435737471;
const ll nINFL = -9187201950435737472;
const int INF = 2139062143;
const int nINF = -2139062144;
const ull ULINF = numeric_limits<ull>::max();
const long double PI = acos(-1);
auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rnd(seed);

inline void IO() {
#ifdef DIVAN
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
#else
    //    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
}

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
        a.resize(n, pi{0, 1});
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
        forn(i, ans.n) {
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
        forn(i, n) {
            forn(j, p.n) {
                ans.a[i + j] = Add(ans.a[i + j], Mul(a[i], p.a[j]));
            }
        }
        ans.Correct();
        return ans;
    }
};

Polynom Interpolation(const vector <pair<T, T>>& coord) {
    int n = sz(coord);
    Polynom ans;
    forn(i, n) {
        Polynom mul(1);
        mul.a[0] = {1, 1};
        forn(j, n) {
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
    cin >> a;
    Polynom ans = Interpolation(a);
    forn(i, ans.n) {
        if (IsInteger()) {
            cout << ans.a[i].first << ' ' << ans.a[i].second << '\n';
        } else {
            cout << setprecision(5) << fixed;
            cout << ans.a[i].first / ans.a[i].second << '\n';
        }
    }
}

signed main() {
    IO();
    int t = 1;
//    cin >> t;
    int startTime = clock();
    for (int i = 1; i <= t; ++i) {
//        cout << "Case #" << i << ": ";
        Solve();
    }
    int endTime = clock();
    fout << '\n' << "Time: " << (endTime - startTime + 999) / 1000;
    return 0;
}
