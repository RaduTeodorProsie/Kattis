#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

/// hint : amazing problem, so I wont spoil too much. You need this to solve it : https://en.wikipedia.org/wiki/Bayes%27_theorem
/*






 ____              _ _             ____  _            _             _
/ ___| _ __   ___ (_) | ___ _ __  | __ )| | ___   ___| | _____ _ __| |
\___ \| '_ \ / _ \| | |/ _ \ '__| |  _ \| |/ _ \ / __| |/ / _ \ '__| |
 ___) | |_) | (_) | | |  __/ |    | |_) | | (_) | (__|   <  __/ |  |_|
|____/| .__/ \___/|_|_|\___|_|    |____/|_|\___/ \___|_|\_\___|_|  (_)
      |_|













*/

int main() {

  constexpr int N = 1e7;
  constexpr int mx = 5e6;
  constexpr int tests = 50;

  std::vector<int> blg = {100};
  while (blg.back() < mx) {
    constexpr double gap = 1.01;
    blg.emplace_back(std::min(static_cast<int>((blg.back() * gap)), mx));
  }

  std::vector<double> ps(blg.size(), 1.0 / static_cast<double>(blg.size()));
  auto poz = [&](const int k) -> double {
    double sum = 0;
    for (int i = 0; i < blg.size(); i++) {
      sum += ps[i] * pow((1.0 - static_cast<double>(blg[i]) / N), k);
    }

    return 1.0 - sum;
  };

  for (int _ = 0; _ <= tests; _++) {
    int ans = 0;
    for (int add = 1 << std::__lg(N); add; add >>= 1) {
      if (poz(ans + add) <= 0.5)
        ans += add;
    }

    ans = std::max(ans, 1);
    if (_ == tests) {
      ans = blg[std::ranges::max_element(ps) - ps.begin()];
      std::cout << "estimate " << ans << std::endl;
      std::cerr << "done";
      return 0;
    }

    std::cout << "test " << ans << std::endl;
    int feedback;
    std::cin >> feedback;
    const double pe = poz(ans);
    if (feedback == 1) {
      for (int i = 0; i < blg.size(); i++)
        ps[i] *= ((1.0 - pow(static_cast<double>(N - blg[i]) / N, ans)) / pe);
    }

    else {
      for (int i = 0; i < blg.size(); i++)
        ps[i] *= (pow(static_cast<double>(N - blg[i]) / N, ans) / (1.0 - pe));
    }
  }
}
