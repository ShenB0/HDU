#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using i128 = __int128;
const int INF = 1 << 30;
const double eps = 1e-7;
const int N =  2e5 + 10;
int a[N], pre[N], suf[N];
void solve(){
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int cur = 0;
    int mx = -INF;
    for (int i = 0; i < n; i++) {
        cur += a[i];
        mx = max(mx, cur);
        if (cur < 0) cur = 0;
        pre[i] = mx;
    }
    cur = 0;
    mx = -INF;
    for (int i = n - 1; i > 0; i--) {
        cur += a[i];
        mx = max(mx, cur);
        if (cur < 0) cur = 0;
        suf[i] = mx;
    }
    int ans = -INF;
    for (int i = 2; i < n - 2; i++) {
        ans = max(a[i] + pre[i - 2] + suf[i + 2], ans);
        // cout << pre[i - 2] << " " << suf[i + 2] << "\n";
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