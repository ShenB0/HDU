#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using i128 = __int128;
const int INF = 1 << 30;
const double eps = 1e-7;
const int N =  3e5 + 10;
int a[N];
void solve(){
    int n;
    cin >> n;
    unordered_map<int, vector<int>> mp;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        mp[x].push_back(i);
    }
    int m;
    cin >> m;
    int cur = n;
    for (int i = 0; i < m; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y;
            cin >> x >> y;
            mp[y].insert(mp[y].end(), mp[x].begin(), mp[x].end());
            mp.erase(x);
        } else if (op == 2) {
            int x;
            cin >> x;
            mp[x].push_back(cur);
            cur++;
        } else {
            int x;
            cin >> x;
            mp.erase(x);
        }
    }
    for (auto& [v, vec] : mp) {
        for (auto id : vec) {
            a[id] = v;
        }
    }
    for (int i = 0; i < cur; i++) {
        if (a[i] == 0) continue;
        cout << a[i] << " ";
        a[i]=0;
    }
    cout << "\n";
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