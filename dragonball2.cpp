#include<iostream>
#include<vector>
#include<bitset>
#include<queue>
#pragma GCC target("avx2")
#pragma GCC optimize("O3","unroll-loops")
using namespace std;
using pii = pair<int,int>;
using ll = int;

///make your own hashes and pray

char p;

inline int getint()
{
    p = ' '; while(p == ' ') p = getchar();
    int read = 0; while(isdigit(p) && !cin.eof())
    {
        read *= 10; read += (p - '0');
        p = getchar();
    }

    return read;
}

constexpr int NMAX = 1e3 + 1;
constexpr int pe = 7573;
constexpr int mod = 60493;

bitset<NMAX> info[NMAX];
vector<pii> vecini[NMAX];

struct stare
{
    int a; bitset<NMAX> ma;
    stare(int aa,bitset<NMAX> &b) : a(aa) {ma = b;}
    bool operator == (const stare& other) const
    {
        return (a == other.a && ma == other.ma);
    }
};

vector<pair<int,pair<int,bitset<NMAX>>>> h[mod];


int has(const pair<int,bitset<NMAX>> s)
{
    return (s.second.count() ^ s.first + (s.first*pe % mod)) % mod;
}

vector<pair<int,pair<int,bitset<NMAX>>>>::iterator getcost(const pair<int,bitset<NMAX>> &s,const int &unde)
{
    for(auto it = h[unde].begin(); it != h[unde].end() ; it++)
        if(it->second.second == s.second) return it;
    return h[unde].end();
}

class cmp
{
    public :
    bool operator()(const pair<int,pair<int,bitset<NMAX>>> &a,const pair<int,pair<int,bitset<NMAX>>> &b)
    {
        return a.first > b.first;
    }
};

ll dijkstra()
{
    int u = has({1,info[1]}); h[u].push_back({0,{1,info[1]}});
    priority_queue<pair<int,pair<int,bitset<NMAX>>>,vector<pair<int,pair<int,bitset<NMAX>>>>,cmp> heap;
    heap.push({0,{1,info[1]}}); while(!heap.empty())
    {
        auto v = heap.top(); heap.pop();
        if(v.second.second.count()>=7) return v.first;
        for(auto &it : vecini[v.second.first])
            {
                int nc = v.first + it.second;
                bitset noua = v.second.second;
                noua |= info[it.first]; pair<int,bitset<NMAX>> g {it.first,noua};
                int unde = has(g); vector<pair<int,pair<int,bitset<NMAX>>>> :: iterator caut = getcost(g,unde);
                if(caut == h[unde].end())
                    {
                        h[unde].push_back({nc,{it.first,noua}});
                        heap.push({nc,{it.first,noua}});
                    }

                else if(caut->first > nc)
                    {
                        caut->first = nc;
                        heap.push({nc,{it.first,noua}});
                    }
            }
    }

    return -1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);

    int n,m,k,a,b,c; dijkstra();
    n = getint(),m = getint(),k = getint();
    for(int i = 0 ; i < m ; i++)
        {
            a = getint(),b = getint(),c = getint();
            vecini[a].push_back({b,c});
            vecini[b].push_back({a,c});
        }

    for(int i = 0 ; i < k ; i++)
        {
            a = getint(),b = getint();
            info[a][b] = 1;
        }

    cout << dijkstra();
}

