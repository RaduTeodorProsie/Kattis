#include<iostream>
#include<vector>
#include<queue>
using namespace std;
using pii = pair<int, int>;

/*Try to write a recursive function that solves this problem

     




 ____              _ _             ____  _            _             _ 
/ ___| _ __   ___ (_) | ___ _ __  | __ )| | ___   ___| | _____ _ __| |
\___ \| '_ \ / _ \| | |/ _ \ '__| |  _ \| |/ _ \ / __| |/ / _ \ '__| |
 ___) | |_) | (_) | | |  __/ |    | |_) | | (_) | (__|   <  __/ |  |_|
|____/| .__/ \___/|_|_|\___|_|    |____/|_|\___/ \___|_|\_\___|_|  (_)
      |_|                                                             




                                                                                                                                                                                                                                                                                                                                                   








*/







class fmcm
{
    public :
    const int oo = 1e9;
    struct muchie
    {
        int cap,flow,cost,to,from;
        muchie(int a,int b,int c,int d,int e) : cap(a),flow(b),cost(c),to(d),from(e){}
    };

    vector<int> pi,real,ta; int s,t;
    vector<vector<int>> vecini;
    vector<muchie> muchii;

    fmcm(int _n,int _s,int _t) : s(_s),t(_t)
    {
        vecini.resize(_n+1); ta.resize(_n+1);
        pi.resize(_n+1,oo); real.resize(_n+1);
    }

    void add(int a,int b,int c,int d)
    {
        vecini[a].emplace_back(muchii.size()); muchii.push_back(muchie(c,0,d,b,a));
        vecini[b].emplace_back(muchii.size()); muchii.push_back(muchie(0,0,-d,a,b));
    }

    void boot()
    {
        queue<int> q; q.push(s); pi[s] = 0;
        bool inq[vecini.size()] = {0};
        while(!q.empty())
            {
                int v = q.front(); q.pop(); inq[v] = 0;
                for(auto &it : vecini[v])
                    {
                        if(!muchii[it].cap) continue;
                        int dist = muchii[it].cost + pi[v];
                        if(dist < pi[muchii[it].to])
                            {
                                pi[muchii[it].to] = dist;
                                if(!inq[muchii[it].to])
                                    {
                                        inq[muchii[it].to] = 1;
                                        q.push(muchii[it].to);
                                    }
                            }
                    }
            }
    }

    void dijkstra()
    {
        vector<int> dist(vecini.size(),oo); fill(real.begin(),real.end(),0);
        priority_queue<pii,vector<pii>,greater<pii>> pq; pq.push({0,s}); dist[s] = 0;
        while(!pq.empty())
            {
                pii varf = pq.top(); pq.pop();
                if(varf.first != dist[varf.second]) continue;
                for(auto &it : vecini[varf.second])
                    {
                        if(!(muchii[it].cap - muchii[it].flow)) continue;
                        int fcost = muchii[it].cost + pi[varf.second] - pi[muchii[it].to];
                        if(dist[muchii[it].to] > dist[varf.second] + fcost)
                            {
                                dist[muchii[it].to] = dist[varf.second] + fcost;
                                ta[muchii[it].to] = it; pq.push({dist[muchii[it].to],muchii[it].to});
                                real[muchii[it].to] = real[varf.second] + muchii[it].cost;

                            }
                    }

            }
    }

    pair<int,int> info()
    {
        int ansf(0),ansc(0);
        boot(); for(;;)
        {
            fill(ta.begin(),ta.end(),-1);
            dijkstra(); int delta = oo; if(ta[t] == -1) break;
            for(int i = ta[t]; i != -1 ; i = ta[muchii[i].from]) delta = min(delta,muchii[i].cap - muchii[i].flow);
            for(int i = ta[t]; i != -1 ; i = ta[muchii[i].from]) muchii[i].flow += delta,muchii[i^1].flow -= delta;
            pi.swap(real); ansf += delta; ansc += delta * pi[t];
        }

        return {ansf,ansc};
    }


};

vector<vector<vector<int>>> ordered;
vector<vector<vector<int>>> want;

int match(int a, int b, vector<vector<int>> &ga, vector<vector<int>> &gb){
		
		if(gb[b].empty()) return ga[a].size();
		if(gb[b].size() > ga[a].size()) return -1;

		int s = gb[b].size() + ga[a].size(); int t = s + 1;
		fmcm cupid(t, s, t);
		for(int i = 0; i < ga[a].size(); i++)
			for(int j = 0; j < gb[b].size(); j++){
					int cost = match(ga[a][i], gb[b][j], ga, gb);
					if(cost != -1) cupid.add(i, ga[a].size() +  j, 1, cost);
			}

		for(int i = 0; i < ga[a].size(); i++)
			cupid.add(s, i, 1, 0);
		for(int i = 0; i < gb[b].size(); i++)
			cupid.add(i + ga[a].size(), t, 1, 0);
		auto rez = cupid.info();
		if(rez.first != gb[b].size()) return -1;
		return rez.second + ga[a].size() - gb[b].size();
}

int main(){
		
		int n, m; cin >> m >> n;
		ordered.resize(n), want.resize(m);

		for(int i = 0; i < m ; i++){
			int sz, x; cin >> sz; sz++; want[i].resize(sz);
			for(int j = 1; j < sz; j++)
				cin >> x, want[i][x].emplace_back(j);
		}

		for(int i = 0; i < n ; i++){
				int sz, x; cin >> sz; sz++; ordered[i].resize(sz);
				for(int j = 1; j < sz; j++)
					cin >> x, ordered[i][x].push_back(j);
		}

		fmcm matcher(n + m + 1, n + m, n + m + 1);
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m ; j++){
				int miau = match(0, 0, ordered[i], want[j]);
				if(miau != -1) matcher.add(i, j + n, 1, miau);
			}

		for(int i = 0; i < n ; i++)
			matcher.add(n + m, i, 1, 0);
		for(int i = 0; i < m ; i++)
			matcher.add(i + n, n + m + 1, 1, 0);
		cout << matcher.info().second;
}
