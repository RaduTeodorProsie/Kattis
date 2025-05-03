#include <algorithm>
#include <iostream>
using namespace std;
using ll = long long;

//hint: find the contribution, or find the expected number of inversions * 2 ^ k
/*






 ____              _ _             ____  _            _             _
/ ___| _ __   ___ (_) | ___ _ __  | __ )| | ___   ___| | _____ _ __| |
\___ \| '_ \ / _ \| | |/ _ \ '__| |  _ \| |/ _ \ / __| |/ / _ \ '__| |
 ___) | |_) | (_) | | |  __/ |    | |_) | | (_) | (__|   <  __/ |  |_|
|____/| .__/ \___/|_|_|\___|_|    |____/|_|\___/ \___|_|\_\___|_|  (_)
      |_|













*/

const int inv2 = 500000004;
constexpr int mod = 1e9 + 7;

void add(int &a, int b) {
  a += b;
  if (a >= mod)
    a -= mod;
}

int fastpow(int a, int b) {
  int rez = 1;
  for (; b; b >>= 1, a = 1LL * a * a % mod)
    if (b & 1)
      rez = 1LL * rez * a % mod;
  return rez;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  string s;
  cin >> s;
  int e1(0), e0(0), ei(0), doi(1);
  for (auto &it : s) {
    if (it == '1')
      add(e1, 1);
    else if (it == '0') {
      add(ei, e1);
      add(e0, 1);
    }

    else {
      add(ei, 1LL * inv2 * e1 % mod);
      add(e1, inv2);
      add(e0, inv2);
    }
  }

  cout << 1LL * ei * fastpow(2, count(s.begin(), s.end(), '?')) % mod;
}
