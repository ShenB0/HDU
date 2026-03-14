//二分+连通图BFS+Dijkstra
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using i128 = __int128;
const ll INF = 1LL << 60;
const double eps = 1e-7;
const int N =  405;
const int MAXN = 2e5 + 5;
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};
int a[N][N], idx[N][N];
int n, m, money, k;
struct Portal{
    int x1, y1, x2, y2; 
    ll w;
}por[MAXN];
int bfs(int t){
    memset(idx, -1, sizeof(idx));
    int cur = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (idx[i][j] != -1 || a[i][j] > t) continue;
            queue<pair<int, int>> q;
            q.push({i, j});
            idx[i][j] = cur;
            while (!q.empty()) {
                auto [x, y] = q.front();
                q.pop();
                for (int k = 0; k < 4; k++) {
                    int nx = x + dx[k];
                    int ny = y + dy[k];
                    if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
                    if (a[nx][ny] <= t && idx[nx][ny] == -1) {
                        idx[nx][ny] = cur;
                        q.push({nx, ny});
                    }
                }
            }
            cur++;
        }
    }
    return cur;
}
bool Dijkstra(int num) {
    vector<vector<pair<int, int>>> adj(num);
    for (int i = 0; i < k; i++) {
        auto& [x1, y1, x2, y2, w] = por[i];
        int u = idx[x1][y1], v = idx[x2][y2];
        if (idx[x1][y1] == -1 || idx[x2][y2] == -1) continue;
        if(u!=v) adj[u].push_back({v, w});
    }
    vector<ll> dist(num, INF);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> q;
    int s = idx[1][1], e = idx[n][m];
    dist[s] = 0;
    q.push({0, s});
    while(!q.empty()){
        auto [d,u] = q.top(); 
        q.pop();
        if (d > dist[u]) continue;
        for (auto& [v, w] : adj[u]){
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                q.push({dist[v],v});
            }
        }
    }
    return dist[e] <= money;

}
bool check(int t){
    int num = bfs(t);
    return Dijkstra(num);
}
void solve(){
    cin >> n >> m >> money >> k;
    int max_t = -1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            max_t = max(a[i][j], max_t);
        }
    }
    for (int i = 0; i < k; i++) {
        int x, y, p, q; 
        ll w;
        cin >> x >> y >> p >> q >> w;
        por[i] = {x, y, p, q, w};
    }
    int l = 0, r = max_t;
    int ans = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans << "\n";
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}