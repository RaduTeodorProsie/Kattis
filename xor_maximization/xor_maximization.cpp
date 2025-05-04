#include <iostream>
using namespace std;
using ll = long long;

const int B = 63;

ll baza[B];

void add(ll x) {
  for (int i = B - 1; i >= 0; i--) {
    if (!(x & (1LL << i)))
      continue;
    if (!baza[i]) {
      baza[i] = x;
      return;
    }

    x ^= baza[i];
  }
}

int main() {
  int n;
  ll x, ans = 0;
  cin >> n;
  while (n--)
    cin >> x, add(x);

  for (int i = B - 1; i >= 0; i--)
    if (!(ans & (1LL << i)))
      ans ^= baza[i];
  cout << ans;
}
