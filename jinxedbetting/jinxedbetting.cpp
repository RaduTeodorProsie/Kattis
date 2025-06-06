#include <cmath>
#include <iostream>
#include <map>
using namespace std;
using ll = long long;

long long steps_to_exceed(const long long N, const long long X,
                          const long long Y) {
  if (N < 2 || X >= Y)
    return 1e18;
  const long long D = (Y - X) + 1;
  const auto T = static_cast<long long>(std::floor(std::log2(N)));
  const long long num_stalls = (D + T - 1) / T - 1;
  return D + num_stalls;
}

bool cycle(const pair<ll, int> &x, const ll j) {
  return (x.first + __lg(x.second) > j);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  int n;
  ll julia;
  cin >> n >> julia;
  map<ll, int, greater<>> fr;
  for (int i = 1; i < n; i++) {
    ll x;
    cin >> x;
    fr[x]++;
  }

  ll ans = 0;
  ll s = fr.begin()->first;
  int f = fr.begin()->second;
  fr.erase(fr.begin());
  for (auto [x, ff] : fr) {
    if (cycle({s, f}, julia))
      break;
    int l = __lg(f);
    ll tx = ans + x;
    ll prep = 1ll * (l + 1) * (s - tx - 1);
    if (steps_to_exceed(f, s, julia) <= prep)
      break;

    ans += prep;
    s += (s - tx - 1) * l;

    if (cycle({s, f}, julia))
      break;
    ans += (l + 1), f += ff, s += l;
  }

  if (cycle({s, f}, julia))
    cout << ans + julia - s;
  else
    cout << ans + steps_to_exceed(f, s, julia) - 1;
}
