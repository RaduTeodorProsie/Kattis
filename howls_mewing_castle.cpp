#include<iostream>
#include<bitset>
using namespace std;

///hint : what happens if N is large?

constexpr int nmax = 24e5 + 1;
const int fz = nmax / 2;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);

    int n, v; cin >> n;
    if(n >= 25) cout << 0;
    else
    {
        bitset<nmax> dp; int ans = 100; 
        for(int i = 0 ; i < n ; i++)
        {
            cin >> v;
            dp |= (dp >> v);
            dp |= (dp << v);
            dp[fz + v] = dp[fz - v] = 1;
        }


        for(int i = fz; i < nmax; i++)
            if(dp[i]) ans = 
                min (ans, __builtin_popcount((i-fz)));
            
        cout << ans;
    }
}


