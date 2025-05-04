#include <algorithm>
#include <iostream>
#include <vector>
#define fi first
#define se second
using namespace std;

struct query {
  int a, b, w, id;
};

class DSU {
private:
  vector<int> t, sz;

public:
  DSU(int n) { t.resize(n + 1, 0), sz.resize(n + 1, 1); };
  int root(int x) { return t[x] ? t[x] = root(t[x]) : x; }
  void unite(int a, int b) { t[a] = b, sz[b] += sz[a]; }
  int getsz(int x) { return sz[root(x)]; }
};

constexpr int nmax = 1e5 + 1;

query e[nmax];
int poz[nmax], ans[nmax];

void sorteaza(vector<query> &v) {
  sort(v.begin(), v.end(),
       [](const query &a, const query &b) { return a.w > b.w; });
}

int main() {
  int n, m, a, b, c, q;
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> a >> b >> c;
    e[i - 1] = {a, b, c, i};
  }

  for (auto &it : ans)
    it = -1;
  sort(e, e + m, [](const query &a, const query &b) { return a.w > b.w; });

  for (int i = 0; i < m; i++)
    poz[e[i].id] = i;

  cin >> q;
  vector<query> todo;
  for (int i = 0; i < q; i++) {
    char op;
    cin >> op;
    if (op == 'S') {
      cin >> a >> b >> c;
      todo.push_back({a, b, c, i});
    }

    else {
      DSU padure(n);
      sorteaza(todo);

      int mi = 0, qi = 0;
      for (auto &it : todo) {
        while (mi < m && e[mi].w >= it.w) {
          int ra = padure.root(e[mi].a), rb = padure.root(e[mi].b);
          if (ra != rb)
            padure.unite(ra, rb);

          mi++;
        }

        int ra = padure.root(it.a), rb = padure.root(it.b);
        if (ra == rb)
          ans[it.id] = 1;
        else
          ans[it.id] = 0;
      }

      cin >> a >> b;
      e[poz[a]].w = b;

      c = poz[a];
      while (c && e[c].w > e[c - 1].w)
        swap(e[c], e[c - 1]), c--;
      while (c + 1 < m && e[c].w < e[c + 1].w)
        swap(e[c], e[c + 1]), c++;
      for (int j = 0; j < m; j++)
        poz[e[j].id] = j;
      todo.clear();
    }
  }

  DSU padure(n);
  sorteaza(todo);

  int mi = 0, qi = 0;
  for (auto &it : todo) {
    while (mi < m && e[mi].w >= it.w) {
      int ra = padure.root(e[mi].a), rb = padure.root(e[mi].b);
      if (ra != rb)
        padure.unite(ra, rb);

      mi++;
    }

    int ra = padure.root(it.a), rb = padure.root(it.b);
    if (ra == rb)
      ans[it.id] = 1;
    else
      ans[it.id] = 0;
  }

  for (int i = 0; i < q; i++)
    if (ans[i] != -1)
      cout << ans[i] << '\n';
}
