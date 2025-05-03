#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


///my favourite <3
///hint : each islander will assume they are not in a triangle untill proven otherwise

/*

     




 ____              _ _             ____  _            _             _ 
/ ___| _ __   ___ (_) | ___ _ __  | __ )| | ___   ___| | _____ _ __| |
\___ \| '_ \ / _ \| | |/ _ \ '__| |  _ \| |/ _ \ / __| |/ / _ \ '__| |
 ___) | |_) | (_) | | |  __/ |    | |_) | | (_) | (__|   <  __/ |  |_|
|____/| .__/ \___/|_|_|\___|_|    |____/|_|\___/ \___|_|\_\___|_|  (_)
      |_|                                                             




                                                                                                                                                                                                                                                                                                                                                   








*/

constexpr int nmax = 1 << 25;

int dp[nmax], seen[nmax], v[25], n, sz;
bool sos[nmax];

int main()
{
    cin >> n;
    for(int i = 0 ; i < n ; i++)
        cin >> v[i];
    for(int i = 0 ; i < n ; i++)
        for(int j = i + 1; j < n; j++)
            for(int k = j + 1; k < n ; k++)
                if((v[i] ^ v[j] ^ v[k])==0)
                {   
                    int ce = (1 << i) | (1 << j) | (1 << k);
                    sos[ce] = 1;
                }
    
    for(int i = 0; i < n; i++)
        for(int j = 1; j < (1 << n); j++)
            if(j & (1 << i)) sos[j] |= sos[j ^ (1 << i)];
    for(int i = 1; i < (1 << n); i++)
    {
        if(!sos[i]) continue;
        
        dp[i] = 1e9;
        for(int b = 0; b < n; b++)
            if(i & (1 << b))
                dp[i] = min(dp[i], dp[i ^ (1 << b)] + 1);
    }
    
    cout << dp[(1 << n) - 1];
}
