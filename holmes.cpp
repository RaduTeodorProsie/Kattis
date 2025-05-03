#include<iostream>
#include<bitset>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

///hint : for every node, try to prove by contradiction wether or not it is true

/*

     




 ____              _ _             ____  _            _             _ 
/ ___| _ __   ___ (_) | ___ _ __  | __ )| | ___   ___| | _____ _ __| |
\___ \| '_ \ / _ \| | |/ _ \ '__| |  _ \| |/ _ \ / __| |/ / _ \ '__| |
 ___) | |_) | (_) | | |  __/ |    | |_) | | (_) | (__|   <  __/ |  |_|
|____/| .__/ \___/|_|_|\___|_|    |____/|_|\___/ \___|_|\_\___|_|  (_)
      |_|                                                             




                                                                                                                                                                                                                                                                                                                                                   








*/

constexpr int nmax = 1e3 + 1;

bitset<nmax> need[nmax], ans;
vector<int> g[nmax]; int grad[nmax], g2[nmax];

void mark(int a)
{
    ans[a] = 1;
    for(auto &it : g[a])
        {
            if(!ans[it])
                mark(it);
        }
}

void surse(int x)
{
    for(int i = 1; i < nmax ; i++)
        if(need[x][i]) cout << i << " ";
    cout << '\n';
}

int main()
{
    int n, m, t, a, b; cin >> n >> m >> t;
    for(int i = 0; i < m ; i++)
        {
            cin >> a >> b; grad[b]++;
            g2[b]++; g[a].emplace_back(b);
        }

    while(t--)
        cin >> a, mark(a);

    queue<int> zero;
    for(int i = 1; i <= n ; i++)
        if(grad[i] == 0) zero.push(i);
    vector<int> top;
    while(!zero.empty())
        {
            int now = zero.front(); zero.pop();
            top.emplace_back(now);
            for(auto &it : g[now])
                {
                    if(--grad[it]==0)
                        zero.push(it);
                }
        }

    for(auto &x : top) ///tatal inainte de fii
        {
            if(!g2[x]) need[x][x] = 1;
            for(auto &it : g[x])
                need[it] |= need[x];
        }

    vector<int> rem;
    for(int i = 1; i <= n ; i++)
        {
            if(ans[i]) continue;
            for(int j = 1; j <= n ; j++)
                {
                    if(!ans[j]) continue;
                    if((need[i] | need[j]) == need[i])
                    {
                        ans[i] = 1;
                        break;
                    }
                }
        }

    for(auto &it : rem) mark(it);
    //for(int i = 1; i <= n ; i++) surse(i);
    for(int i = 1; i <= n ; i++)
        if(ans[i]) cout << i << " ";

}
