#include <iostream>
#include <vector>
using namespace std;

int main() {
    int d, g, n, k;
    cin >> d >> g >> n >> k;

    const int S = d + g;

    vector<vector<int>> dp(k + 1, vector<int>(S + 1, 1e9));
    vector<vector<int>> odp = dp;

    for (int b = 0; b <= S; b++)
        odp[0][b] = b;

    for (int i = n - 1; i >= 0; i--) {

        for (int b = 0; b <= S; b++) {
            dp[0][b] = b;
        }

        for (int j = 1; j <= k; j++) {
            for (int b = 0; b <= S; b++) {
                auto &B = odp[j];
                auto &A = odp[j - 1];
                int ans = 0;
                const int up = min(b, S - b);

                for (int add = 2048; add; add >>= 1) {
                    if (ans + add > up)
                        continue;
                    if (A[b + ans + add] <= B[b - ans - add]) {
                        ans += add;
                    }
                }

                dp[j][b] = A[b + ans];
            }
        }
        swap(dp, odp);
    }

    cout << odp[k][d];
}