#include <iostream>
#include <queue>
#include <vector>

///hint : you have relatively few bottles, and the answer is relatively small. 
/*

     




 ____              _ _             ____  _            _             _ 
/ ___| _ __   ___ (_) | ___ _ __  | __ )| | ___   ___| | _____ _ __| |
\___ \| '_ \ / _ \| | |/ _ \ '__| |  _ \| |/ _ \ / __| |/ / _ \ '__| |
 ___) | |_) | (_) | | |  __/ |    | |_) | | (_) | (__|   <  __/ |  |_|
|____/| .__/ \___/|_|_|\___|_|    |____/|_|\___/ \___|_|\_\___|_|  (_)
      |_|                                                             




                                                                                                                                                                                                                                                                                                                                                   








*/

void solve() {
    constexpr int vmax = 4500;
    int wine, bottles;
    std::cin >> wine >> bottles;
    wine *= 1000;
    std::vector<int> mars(vmax + 2);
    int modulo = 1e9;
    for (int i = 0; i < bottles; i++) {
        int lo, hi;
        std::cin >> lo >> hi;
        mars[lo] += 1;
        mars[hi + 1] -= 1;
        modulo = std::min(modulo, lo);
    }

    std::vector<int> dp(modulo, 1e9);
    std::vector<int> edg;
    dp[0] = 0;
    for (int i = 1; i <= vmax; i++) {
        mars[i] += mars[i - 1];
        if (mars[i])
            edg.push_back(i);
    }

    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>> , std::greater<>> pq; pq.emplace(0, 0);
    while (!pq.empty()) {
        auto [cost, node] = pq.top(); pq.pop();
        if (cost != dp[node])
            continue;
        for (const auto &adj : edg) {
            if (const int tgt = (node + adj) % modulo; dp[tgt] > adj + cost) {
                dp[tgt] = cost + adj;
                pq.emplace(cost + adj, tgt);
            }
        }
    }

    int gans = 1e9;
    for (int ans = wine; ans >= wine - modulo; ans--) {
        if (dp[ans % modulo] <= ans) {
            std::cout << wine - ans << '\n';
            return;
        }
    }

    std::cout << gans << '\n';
}

int main() {
    int _;
    std::cin >> _;
    while (_--)
        solve();
}
