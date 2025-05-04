#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <unordered_map>
#include <vector>
#define fi first
#define se second
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using ld = double;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

constexpr int NMAX = 1e6 + 1;
constexpr int mod = 1e9 + 7;

map<int, string> dp[101];

void baga(int i, int v, string &s) {
  if (!dp[i].count(v) || s < dp[i][v])
    dp[i][v] = s;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  int n, a[101], b[101];
  cin >> n;
  dp[0][0] = "";
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  for (int i = 1; i <= n; i++)
    cin >> b[i];
  for (int i = 1; i <= n; i++) {
    for (auto &s : dp[i - 1]) {
      int val = s.fi;
      string ans = s.se;
      ans += "A";
      baga(i, val + a[i], ans);
      ans.pop_back();
      ans += "B";
      baga(i, val - b[i], ans);
    }
  }

  int vans = 1e9;
  string sans;
  for (auto &it : dp[n]) {
    if (abs(it.fi) < vans) {
      vans = abs(it.fi);
      sans = it.se;
    } else if (abs(it.fi) == vans) {
      if (it.se < sans)
        sans = it.se;
    }
  }

  cout << sans;
}