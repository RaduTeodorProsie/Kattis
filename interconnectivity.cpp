#include<iostream>
#include<vector>
using namespace std;

struct DSU
{
    vector<int> t, sz; 
    vector<pair<int &, int>> last;
    DSU(int n)
    {
        t.resize(n + 1, 0);
        sz.resize(n + 1, 1);
    }
    
    int root(int x){return t[x] ? root(t[x]) : x;}
    void unite(int a, int b)
    {
        a = root(a), b = root(b);
        if(a == b) return;
        
        if(sz[a] < sz[b]) swap(a, b);
        last.push_back({sz[a], sz[a]});
        last.push_back({t[b], 0});
        
        t[b] = a; sz[a] += sz[b];
        
    }
    
    void undo()
    {
        while(!last.empty())
        {
            last.back().first = last.back().second;
            last.pop_back();
        }
    }
};

constexpr int nmax = 1e5 + 1;

pair<int,int> muchii[nmax], toate[nmax * 10];
vector<int> alive; int ans[nmax * 10], md; 


void dfs(int pref, DSU &padure, vector<int> &qu, int b)
{   
    if(qu.empty()) return;
    if(b == -1)
    {
        for(auto &it : qu)
            ans[it] = pref;
        return;
    }
    
    ///alive tine muchiile care pot fi adaugate
    
    pref ^= (1 << b);
    for(auto &it : alive)
    {
        if(pref == (it | pref))
            padure.unite(muchii[it].first, muchii[it].second);  
    }
    
    vector<int> st, dr, good;
    for(auto &it : qu)
    {
        if(padure.root(toate[it].first) == padure.root(toate[it].second))
            st.emplace_back(it);
        else dr.emplace_back(it);
    }
    
    for(auto &it : alive)
    {
        if(pref == (it | pref))
            good.emplace_back(it);
    }
    
    padure.undo(); alive.swap(good);
    dfs(pref, padure, st, b - 1); alive.swap(good);
    dfs(pref | (1 << b), padure, dr, b - 1);        
}

int main()
{   
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    int n, m, a, b, q; cin >> n >> m;
    for(int i = 1; i <= m ; i++)
        cin >> muchii[i].first >> muchii[i].second;
    cin >> q; 
    for(int i = 0 ; i < 30 ; i++) 
        if(m & (1 << i)) md = i;
    for(int i = 0 ; i < q ; i++)
    {
        cin >> a >> b;
        toate[i] = {a, b};
    }
    
    DSU padure(n); vector<int> qu(q);
    for(int i = 1; i <= m ; i++) alive.emplace_back(i);
    for(int i = 0; i < q ; i++) qu[i] = i;
    dfs((1 << (md + 1)) - 1, padure, qu, md);
    for(int i = 0 ; i < q ; i++)
        cout << ans[i] << '\n';
}